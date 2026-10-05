# 项目理解报告

请尽量使用自己的语言回答以下问题。可以引用少量关键代码或伪代码，但不要只粘贴实现。
完成一节后删除该节末尾的待填写标记；本地检查会拒绝仍有未完成章节的报告。

## 1. 图像生命周期与所有权

`ImageSequenceSource` 中的 `buffer_` 用来模拟相机内部会重复使用的图像缓冲区。每次读取新图片后，都会通过 `raw.copyTo(buffer_)` 把新像素写进同一个 `buffer_`。这样可以避免相机每次都重新管理一块新的缓冲区，但也意味着下一次读取可能覆盖上一次的数据。

`cv::Mat` 本身主要是一个管理图像信息的对象，真正的像素数据在另外的缓冲区中。普通赋值 `frame.image = buffer_` 只是浅拷贝，两个 `cv::Mat` 会共享同一份像素数据。因此如果 `buffer_` 之后被相机复用，已经放入队列的旧 `Frame` 看到的图像也可能一起变化。

我的修改是：

```cpp
frame.image = buffer_.clone();
```

`clone()` 会进行深拷贝，使这个 `Frame` 得到一份独立的像素数据。这样 `Frame` 进入队列后就拥有自己独立的图像内容，之后 `ImageSequenceSource` 再次写入 `buffer_` 时，不会改变已经交给 worker 的旧帧，因此校验值仍然能够和图像内容保持一致。

## 2. 并发处理与恰好一次

producer 读取一帧后，通过 `BlockingQueue::push()` 把一个 `Frame` 放入队列。多个 worker 都在调用 `pop()`，但是 `BlockingQueue` 内部用 mutex 保护队列，所以同一个队首元素只会被一个 worker 取走。一个 worker 取走后该元素就从队列中删除，因此不会有两个 worker 同时处理同一帧。

producer 对每个成功读取的输入只执行一次 `push()`，worker 则对每个成功 `pop()` 出来的帧执行一次处理和保存，所以正常情况下不会重复处理。输入耗尽后 producer 调用 `queue_.close()`。`close()` 会唤醒正在等待的 worker，但关闭队列并不会直接丢弃已经入队的数据：只要队列仍然非空，`pop()` 仍会继续取出已有帧；只有队列已经关闭并且为空时，`pop()` 才返回 `false`，worker 的循环结束。

因此，输入结束时已经在处理某一帧的 worker 会完成当前处理；队列中还没处理的帧会继续被其他 worker 取走；没有数据可取而正在等待的 worker 会被 `close()` 唤醒，并在确认队列为空后正常退出。这样既不会漏掉已经入队的帧，也不会重复处理同一个队列元素。

在 producer 中我使用：

```cpp
queue_.push(std::move(frame));
```

这里使用了课堂中介绍的移动语义，把当前 `Frame` 的资源交给队列，避免一次不必要的额外拷贝。下一次调用 `source_->next(frame)` 时会重新给这个 `frame` 写入新的 id、校验值和图像。

## 3. 共享统计数据

`Statistics` 会被多个线程访问。producer 会更新 `produced`；多个 worker 会更新 `processed`、`saved` 和 `corrupted`；调用 `statistics()` 的线程会通过 `snapshot()` 读取这些计数。

原来的 `deliberatelySlowIncrement()` 是一个“读取旧值，再写回旧值加一”的过程。如果两个 worker 同时执行，例如它们都先读到 `processed_ == 5`，之后都写入 6，那么实际上发生了两次处理，但计数只增加一次。这就是多个线程同时访问共享数据产生的数据竞争。

我的做法是在 `Statistics` 中增加一个 `std::mutex`，并在每一个更新函数中使用：

```cpp
std::lock_guard<std::mutex> lock(mutex_);
```

`lock_guard` 构造时自动加锁，离开函数作用域时自动解锁，符合课堂中介绍的 RAII 用法。这样同一时刻只有一个线程能修改这些计数，不会发生丢失更新。

`snapshot()` 也使用同一个 mutex。这样读取四个计数时，其他线程不能在中间修改它们，因此返回的是同一个受保护临界区中的一致快照。由于 `snapshot()` 是 `const` 成员函数，所以 mutex 声明为 `mutable`，只允许同步操作本身在 `const` 函数中改变锁的状态，并不会改变统计数据的逻辑含义。

## 4. 线程关闭协议

### 1. `start()` 后显式调用 `wait()`

`start()` 先创建多个 worker 线程，再创建 producer 线程。producer 不断读取输入并把帧放进队列，输入耗尽后调用 `queue_.close()`。worker 会继续取完队列中剩余的数据，然后在“队列已关闭且为空”时让 `pop()` 返回 `false`，从而退出循环。

`wait()` 先对 producer 调用 `join()`，保证 producer 已经结束，也就保证它已经执行了正常的队列关闭流程；然后依次 `join()` 所有 worker，等待它们处理完剩余帧并退出。`wait()` 返回时，所有线程都已经被回收，因此随后销毁 `Pipeline` 时不会留下仍然运行的线程，也不会访问已经析构的成员对象。

### 2. `start()` 后不调用 `wait()`，直接析构 `Pipeline`

我让 `Pipeline::~Pipeline()` 直接调用 `wait()`。这样即使调用者忘记显式等待，析构函数也会先等待 producer 结束，再等待所有 worker 结束，最后才继续销毁 `Pipeline` 的成员。

这是 RAII 的思想：线程资源的生命周期由 `Pipeline` 对象负责管理。`std::thread` 如果在仍然 `joinable` 时直接析构会触发 `std::terminate`，所以析构函数中的 `wait()` 保证所有已经启动的线程先被 `join()`。同时，线程结束后才销毁 `queue_`、`source_`、`statistics_` 等成员，因此不会出现线程继续访问已经被销毁对象的悬空访问。

`wait()` 中在调用 `join()` 前都会先检查 `joinable()`。线程一旦已经被 `join()`，再次调用 `wait()` 时就不会再次 `join()` 它，因此当前实现允许 `wait()` 被重复调用；析构函数在调用者已经显式执行过 `wait()` 的情况下再次调用也不会有问题。

