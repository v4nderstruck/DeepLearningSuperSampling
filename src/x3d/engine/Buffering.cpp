#include "Buffering.hpp"
#include <iostream>
using namespace x3d::engine;

BufferManager::BufferManager(size_t size): size(size), frame(0) {
  sempahore = dispatch_semaphore_create(size);
  
}

void BufferManager::manageThis(
    std::vector<NS::SharedPtr<MTL::Buffer>> &&manageBuffer) {
  if (manageBuffer.size() == 0 || manageBuffer.size() != size) {
    std::cout << "BufferManager::manageThis: buffers.size() == " << manageBuffer.size()
              << " || buffers.size() != " << size << std::endl;
    return;
  }
  buffers = std::move(manageBuffer);
}

MTL::Buffer* BufferManager::nextBuffer() {
  dispatch_semaphore_wait(sempahore, DISPATCH_TIME_FOREVER);
  auto buffer = buffers[frame].get();
  frame = (frame + 1) % size;
  return buffer;
}

void BufferManager::freeBuffer() {
  dispatch_semaphore_signal(sempahore);
}
