#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "core.h"

void produce(treasure_chest::pattern::SyncQueue<int> &q) {
  for (int i = 0; i < 999; ++i) {
    std::cout << "produce: " << i << std::endl;
    q.Enqueue(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

void consume(treasure_chest::pattern::SyncQueue<int> &q) {
  while (true) {
    int task = q.Dequeue();
    std::cout << "consume: " << task << std::endl;
  }
}

int main(int argc, char *argv[]) {
  treasure_chest::pattern::SyncQueue<int> sync_queue;
  std::thread thread_a(produce, std::ref(sync_queue));
  std::thread thread_b(consume, std::ref(sync_queue));

  thread_a.join();
  thread_b.join();

  return 0;
}