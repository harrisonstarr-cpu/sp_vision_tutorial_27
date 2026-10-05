# nav_lecture4小作业：Qos_debugger
这道题的目标就是让你快速上手、理解什么是ros。抛开复杂的概念，ros本质上完成的任务就是便利的进程间通信。比如，我有两个进程，一个进程发布雷达数据，另一个进程接收。使用ros就可以方便的完成通讯。你可以搜索以下，发送信息有哪些类型，分别有何特点。特别注意，不同的信息传输方式有不同的质量要求。你不会允许送的外卖没到你手上，但是一个电话过来，也许漏接了也无所谓，可能只是个诈骗。ros2也是这样。重点关注这一点会对这道题有所帮助

> 环境要求：ROS2 Humble

## 包结构

```
src/
  nav_hw_interfaces/     # 接口包：只放 .msg，无业务代码
    msg/SensorData.msg   # 可以打开.msg文件查看接口详细内容
  qos_debugger/          # 业务节点包
    src/qos_debugger_pub.cpp   # 发布 /SensorData
    src/qos_debugger_sub.cpp   # 订阅 /SensorData
```

## 编译

```bash
cd lecture4/homework
colcon build 
source install/setup.bash
```


## 任务一：实现pub和sub的通信

```bash
ros2 -h     //有忘记的命令就输入-h去查询用法
```

**现象**：启动pub和sub节点后sub节点订阅不到任何消息
提示：如果两个节点不能通过话题通信，我们应该如何区查看话题的详细信息（有没有相关的命令）
任务一仅修复qos_debugger_pub.cpp的一处或几处代码即可完成


---

## 任务二：为什么收到的消息会丢包？/(ㄒoㄒ)/~~

第一问找到问题并修改代码后，记得重新
```colcon build```
```source install/setup.bash```
**现象**：sub会打印黄色的warning输出告诉你丢包的序列，每秒还会打印出丢包率

提示：
有没有什么命令可以查看节点的配置(ros2 param -h)
可以通过修复qos_debugger_sub.cpp中的一处或几处代码解决该问题（可能会有多种解决方法）

## 任务三：把收到的消息的帧率计算并打印出来（放在定时器回调函数中每秒打印一次即可）
补全qos_debugger_sub.cpp即可



在下面按顺序完成三个任务，要求把用到的命令放入代码块中并讲解命令，每一问最好加入自己的理解



任务一：实现 pub 和 sub 的通信
1. 问题现象
最开始运行 pub 和 sub 后，subscriber 无法收到 /sensor_data 的消息。
遇到两个节点无法通过 Topic 通信时，我首先使用下面的命令检查当前话题：
ros2 topic list
该命令用于查看当前 ROS2 系统中存在的 Topic。
然后查看 /sensor_data 的详细信息：
ros2 topic info /sensor_data --verbose
原发布端的 QoS 为：
Reliability: BEST_EFFORT
而订阅端默认配置为：
Reliability: RELIABLE
2. 问题原因
发布者使用 BEST_EFFORT，表示它只能“尽力发送”，并不保证每一条消息都可靠送达；订阅者使用 RELIABLE，表示它要求可靠传输。
此时订阅者要求的可靠性高于发布者能够提供的可靠性，所以 QoS 不兼容，subscriber 无法正常收到消息。
3. 修改方法
在 qos_debugger_pub.cpp 中，原代码为：
this->declare_parameter("reliability", "best_effort");
修改为：
this->declare_parameter("reliability", "reliable");
这样 publisher 和 subscriber 默认都使用 RELIABLE，QoS 可以匹配。
修改后重新编译：
colcon build
source install/setup.bash
然后重新启动两个节点。
4. 我的理解
这一问让我认识到，ROS2 中 Topic 名称和消息类型相同并不代表一定能够通信，QoS 也是通信接口的一部分。
实际机器人系统中，高频传感器数据可能更加关注实时性，因此允许偶尔丢失一帧；而重要状态或控制信息则可能更加关注可靠性。因此 QoS 应该根据数据特点选择，而不是一味认为 Reliable 一定优于 Best Effort。




任务二：为什么收到的消息会丢包
1. 问题现象
完成任务一以后，subscriber 已经能够收到数据，但是程序会出现黄色 warning
查看 subscriber 的参数：
ros2 param list /sensor_subscriber
其中包括：
callback_delay_ms
depth
reliability
查看回调延迟参数：
ros2 param get /sensor_subscriber callback_delay_ms
原程序默认值为：
30 ms
发布端发送频率可以通过参数查看：
ros2 param get /sensor_publisher rate
发布频率为：
100 Hz
2. 问题原因
发布端频率为 100 Hz：
1 / 100 s = 10 ms
即每 10 ms 产生一条消息。
subscriber 回调中原来存在：
std::this_thread::sleep_for(
    std::chrono::milliseconds(callback_delay_ms_));
而 callback_delay_ms 默认是 30 ms。
因此订阅端理论上每秒最多只能处理大约：
1000 / 30 ≈ 33 条消息
但发布端每秒发送约 100 条消息，所以 subscriber 的处理速度明显跟不上 publisher。
同时订阅端 QoS 使用：
rclcpp::KeepLast(depth_)
默认 depth = 10，即缓存队列只保存有限数量的最新消息。当回调处理过慢、缓存持续积压后，旧消息会被覆盖或丢弃，于是 seq 出现跳变，程序检测到丢包。
3. 代码修改
在 qos_debugger_sub.cpp 中，将：
this->declare_parameter("callback_delay_ms", 30);
修改为：
this->declare_parameter("callback_delay_ms", 0);
这样默认情况下不会故意阻塞 subscriber 的 callback。
4. 我的理解
任务一解决的是“双方能不能建立正常通信”，任务二解决的是“建立通信以后能不能及时处理消息”。




任务三：计算接收到消息的帧率
1. 实现思路
程序中的 received_count_ 表示从程序启动以后累计接收到的消息数量。
如果直接每秒打印 received_count_，得到的会是累计值，并不是每秒的帧率。
因此需要记录上一次统计时的累计接收数量：
uint32_t last_received_count_{0};
这一秒新收到的消息数量为：
received_count_ - last_received_count_
同时使用：
std::chrono::steady_clock::time_point last_report_time_
记录上一次统计时间，计算真实经过的时间。
最终帧率计算公式为：
FPS = 本周期新收到的消息数量 / 实际经过时间
2. report() 中加入的代码
auto now = std::chrono::steady_clock::now();

double elapsed =
    std::chrono::duration<double>(
        now - last_report_time_).count();

uint32_t received_since_last =
    received_count_ - last_received_count_;

double fps =
    (elapsed > 0.0)
        ? static_cast<double>(received_since_last) / elapsed
        : 0.0;

RCLCPP_INFO(
    this->get_logger(),
    "接收帧率: %.2f Hz",
    fps);

last_received_count_ = received_count_;
last_report_time_ = now;
使用实际经过时间而不是直接假设“定时器一定精确为 1 秒”，可以使统计结果更加严谨。
正常情况下，publisher 设置为 100 Hz，subscriber 不存在明显阻塞时，输出应该接近：
累计: 收到 100 条, 丢失 0 条, 丢包率 0.00%
接收帧率: 99.xx Hz
或者：
接收帧率: 100.xx Hz
由于操作系统调度和定时器本身存在少量误差，实际结果不一定严格等于 100.00 Hz，这是正常现象。
3. 我的理解
帧率本质上就是单位时间内成功接收到的消息数量。
这一问不仅是在练习 ROS2 的 timer，也让我理解到，在实际系统中不能只看“有没有消息”，还需要通过频率和丢包率等指标判断通信质量。
例如传感器理论发布频率为 100 Hz，但 subscriber 实际只能收到 30 Hz，那么即使程序表面上一直有数据输出，也说明系统中仍然存在性能问题。
