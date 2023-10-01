#pragma once
#include <Metal/Metal.hpp>
namespace x3d {
namespace mesh {
class Mesh {
public:
  virtual void render(MTL::RenderCommandEncoder* encoder) = 0;

private: 
  MTL::Buffer* pBuffer;
  long bufferIdx;
  long vertexCount;
  MTL::PrimitiveType primitiveType;
};
}
}
