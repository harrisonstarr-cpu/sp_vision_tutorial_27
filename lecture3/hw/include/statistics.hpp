#pragma once

#include <mutex>

struct StatisticsSnapshot
{
    int produced = 0;
    int processed = 0;
    int saved = 0;
    int corrupted = 0;
};

class Statistics
{
public:
    void onProduced();
    void onProcessed();
    void onSaved();
    void onCorrupted();
    StatisticsSnapshot snapshot() const;

private:
    // Statistics 会被 producer、多个 worker 以及读取快照的线程共同访问。
    // 使用 mutex 保护这些共享计数，避免数据竞争。
    mutable std::mutex mutex_;
    int produced_ = 0;
    int processed_ = 0;
    int saved_ = 0;
    int corrupted_ = 0;
};

