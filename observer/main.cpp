#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include "core.h"

class MessageSeeta : public treasure_chest::pattern::MessageBase {
 public:
  std::string name() const { return "Seeta.\n"; }
};

class TestObserverA : public treasure_chest::pattern::Observer<MessageSeeta> {
  void OnNotify(const MessageSeeta& msg) override {
    std::cout << "Hello, I am TestObserverA.\n";
    std::cout << "This is the msg I received: " << msg.name() << std::endl;
  }
};

class TestSubjectA : public treasure_chest::pattern::Subject {
 public:
  void Run() { Notify(MessageSeeta{}); }
};

int main(int argc, char* argv[]) {
  std::shared_ptr<TestObserverA> observer_a(new TestObserverA);
  std::shared_ptr<TestObserverA> observer_b(new TestObserverA);
  TestSubjectA subject_a;
  subject_a.AddObserver<MessageSeeta>(observer_a);
  subject_a.AddObserver<MessageSeeta>(observer_b);

  subject_a.Run();

  observer_a.reset();

  subject_a.Run();

  return 0;
}