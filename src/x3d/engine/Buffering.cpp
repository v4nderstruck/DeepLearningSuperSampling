#include "Buffering.hpp"
#include <iostream>
using namespace x3d::engine;

BufferManager::BufferManager(size_t size): size(size) {
  sempahore = dispatch_semaphore_create(size);
  
}

void BufferManager::manageThis(
    std::vector<NS::SharedPtr<MTL::Buffer>> buffers) {
  if (buffers.size() == 0 || buffers.size() != size) {
    std::cout << "BufferManager::manageThis: buffers.size() == " << buffers.size()
              << " || buffers.size() != " << size << std::endl;
    return;
  }
  buffers = buffers;
}
