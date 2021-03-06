﻿#include "pch.h"
#include "aiThreadPool.h"

#ifndef aiWithTBB

class aiWorkerThread
{
public:
    void operator()();
};


void aiWorkerThread::operator()()
{
    aiThreadPool &pool = aiThreadPool::getInstance();
    std::function<void()> task;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(pool.m_queue_mutex);
            while (!pool.m_stop && pool.m_tasks.empty()) {
                pool.m_condition.wait(lock);
            }
            if (pool.m_stop) { return; }

            task = pool.m_tasks.front();
            pool.m_tasks.pop_front();
        }
        task();
    }
}

aiThreadPool::aiThreadPool(size_t threads)
    : m_stop(false)
{
    for (size_t i = 0; i < threads; ++i) {
        m_workers.push_back(std::thread(aiWorkerThread()));
    }
}

aiThreadPool::~aiThreadPool()
{
    m_stop = true;
    m_condition.notify_all();

    for (auto& worker : m_workers) {
        worker.join();
    }
}

aiThreadPool& aiThreadPool::getInstance()
{
    static aiThreadPool s_instance(std::thread::hardware_concurrency());
    return s_instance;
}

void aiThreadPool::enqueue(const std::function<void()> &f)
{
    {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        m_tasks.push_back(std::function<void()>(f));
    }
    m_condition.notify_one();
}



aiTaskGroup::aiTaskGroup()
    : m_active_tasks(0)
{
}

aiTaskGroup::~aiTaskGroup()
{
}

void aiTaskGroup::wait()
{
    aiThreadPool &pool = aiThreadPool::getInstance();
    while (m_active_tasks > 0)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(pool.m_queue_mutex);
            if (!pool.m_tasks.empty()) {
                task = pool.m_tasks.front();
                pool.m_tasks.pop_front();
            }
        }
        if (task) { task(); }
    }
}

#endif // aiWithTBB
