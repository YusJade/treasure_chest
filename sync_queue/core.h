
#include <condition_variable>
#include <deque>
#include <mutex>
namespace treasure_chest {
namespace pattern {
template <typename TaskType>
class SyncQueue {
 public:
  void Enqueue(const TaskType& task) {
    std::unique_lock<std::mutex> lock(mutex_);
    deque_.push_back(task);
    // 唤醒线程
    condition_var_.notify_all();
  }

  TaskType Dequeue() {
    std::unique_lock<std::mutex> lock(mutex_);
    // 队列为空时阻塞队列
    condition_var_.wait(lock, [this] { return !deque_.empty(); });
    TaskType task = deque_.front();
    deque_.pop_front();
    return std::move(task);
  }

 private:
  std::deque<TaskType> deque_;
  std::mutex mutex_;
  std::condition_variable condition_var_;
};
}  // namespace pattern
}  // namespace treasure_chest