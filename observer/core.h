#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace treasure_chest {
namespace pattern {
class MessageBase {
 public:
  virtual ~MessageBase() = default;
};

class ObserverBase {};

template <typename T>
class Observer : public ObserverBase {
 public:
  virtual ~Observer() = default;
  virtual void OnNotify(const T& message) = 0;
};

class Subject {
  typedef std::vector<std::weak_ptr<ObserverBase>> ObserverList;

 private:
  std::unordered_map<std::type_index, ObserverList> observers_;

 public:
  template <typename T>
  void AddObserver(std::shared_ptr<Observer<T>> observer) {
    // 包装 OnNotify。
    auto wrapper = std::static_pointer_cast<ObserverBase>(observer);
    observers_[typeid(T)].push_back(wrapper);
  }

  template <typename T>
  void Notify(const T& message) {
    // 根据消息类型获取对应的观察者列表。
    auto it = observers_.find(typeid(T));
    if (it == observers_.end()) {
      return;
    }

    auto& observers_list = it->second;
    for (auto observer_it = observers_list.begin();
         observer_it != observers_list.end();) {
      if (auto locked_observer = observer_it->lock()) {
        auto observer_ptr =
            std::static_pointer_cast<Observer<T>>(locked_observer);
        observer_ptr->OnNotify(message);
        ++observer_it;
      } else {
        // 若观察者的内存已被释放，则将其移除。
        observer_it = observers_list.erase(observer_it);
      }
    }
  }
};

}  // namespace pattern
}  // namespace treasure_chest