#include <cstdint>
#include <iostream>
#include <thread>

#include "producer_consumer/core.h"

class Camera : public treasure_chest::pattern::Producer<int8_t *> {
 public:
  Camera(treasure_chest::pattern::SyncQueue<int8_t *> &q)
      : treasure_chest::pattern::Producer<int8_t *>(q) {}

  void CaptureFrame() {
    while (true) {
      int8_t *frame = new int8_t[100];
      sync_queue_.Enqueue(frame);
      std::cout << "Push task -> frame size: " << sizeof(frame) << std::endl;
    }
  }
};

class Seeta : public treasure_chest::pattern::Consumer<int8_t *> {
 public:
  Seeta(treasure_chest::pattern::SyncQueue<int8_t *> &q)
      : treasure_chest::pattern::Consumer<int8_t *>(q) {}

  void Deal() {
    while (true) {
      int8_t *frame = sync_queue_.Dequeue();
      std::cout << "Get task -> frame size: " << sizeof(frame) << std::endl;
    }
  }
};

int main() {
  treasure_chest::pattern::SyncQueue<int8_t *> q;
  Camera cam(q);
  Seeta seeta(q);

  std::thread thread_cam(&Camera::CaptureFrame, &cam);
  std::thread thread_seeta(&Seeta::Deal, &seeta);

  thread_seeta.join();
  thread_cam.join();

  return 0;
}