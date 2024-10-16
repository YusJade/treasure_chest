#include "sync_queue/core.h"

namespace treasure_chest {
namespace pattern {
template <typename TaskType>
class Producer {
 public:
  Producer() = delete;
  Producer(SyncQueue<TaskType> &q) : sync_queue_(q) {}

 protected:
  SyncQueue<TaskType> &sync_queue_;
};

template <typename TaskType>
class Consumer {
 public:
  Consumer() = delete;
  Consumer(SyncQueue<TaskType> &q) : sync_queue_(q) {}

 protected:
  SyncQueue<TaskType> &sync_queue_;
};
}  // namespace pattern
}  // namespace treasure_chest