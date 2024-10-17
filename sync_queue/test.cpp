#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "core.h"

void produce(treasure_chest::pattern::SyncQueue<int> &q) {
  for (int i = 0; i < 999; ++i) {
    std::cout << "produce: " + std::to_string(i) + "\n";
    q.Enqueue(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void consume(treasure_chest::pattern::SyncQueue<int> &q) {
  while (true) {
    int task = q.Dequeue();
    std::cout << "consume: " + std::to_string(task) + "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
}

int main(int argc, char *argv[]) {
  treasure_chest::pattern::SyncQueue<int> sync_queue(100);
  std::thread thread_a(produce, std::ref(sync_queue));
  std::thread thread_b(consume, std::ref(sync_queue));
  std::thread thread_c(consume, std::ref(sync_queue));
  std::thread thread_d(consume, std::ref(sync_queue));
  std::thread thread_e(consume, std::ref(sync_queue));

  thread_a.join();
  thread_b.join();
  thread_c.join();
  thread_d.join();
  thread_e.join();

  return 0;
}