#pragma once

#include <Metal/Metal.hpp>
#include <vector>

namespace x3d {
namespace engine {

enum ArgumentBufferIndex {
  VERTICES = 0,
  UNIFORMS = 1,
  MODELS = 2
};

class BufferManager {
public:
  BufferManager(size_t size);
  void manageThis(std::vector<NS::SharedPtr<MTL::Buffer>> buffers);
  void freeBuffer();
private:
  std::vector<NS::SharedPtr<MTL::Buffer>> buffers;
  size_t size;
  int frame;
  dispatch_semaphore_t sempahore;
};

} // namespace engine
} // namespace x3d
