#pragma once

#include <condition_variable>
#include <cstdio>
#include <deque>
#include <mutex>

namespace treasure_chest {
namespace pattern {
template <typename TaskType>
class SyncQueue {
 public:
  SyncQueue(int max_size = 1000) : max_size_(max_size) {}

 public:
  void Enqueue(const TaskType& task) {
    std::unique_lock<std::mutex> lock(mutex_);
    // 队列为满时阻塞队列
    condition_var_.wait(lock, [this] { return deque_.size() < max_size_; });
    deque_.push_back(task);
    // 唤醒其他线程
    condition_var_.notify_all();
  }

  TaskType Dequeue() {
    std::unique_lock<std::mutex> lock(mutex_);
    // 队列为空时阻塞队列
    auto start = std::chrono::high_resolution_clock::now();
    printf("waiting for task...\n");
    condition_var_.wait(lock, [this] { return !deque_.empty(); });
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // printf("syncqueue wait for task %f s", duration.count());
    TaskType task = deque_.front();
    deque_.pop_front();
    // 唤醒其他线程
    condition_var_.notify_all();
    return std::move(task);
  }

  int TaskQuantity() const { return deque_.size(); }

 private:
  std::deque<TaskType> deque_;
  int max_size_;
  std::mutex mutex_;
  std::condition_variable condition_var_;
};
}  // namespace pattern
}  // namespace treasure_chest