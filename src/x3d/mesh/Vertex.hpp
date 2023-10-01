#pragma once
#include <simd/simd.h>
#include <Metal/Metal.hpp>
#include <vector>

namespace x3d {
namespace mesh {

class Vertex {
public:
  static Vertex create(simd::float3 position, simd::float3 normal, simd::float4 color, simd::float2 textureCoordinate);
  static NS::SharedPtr<MTL::Buffer> toBuffer(MTL::Device* device, std::vector<Vertex>& vertexVec);
  void debug_size();
private:  
  simd::float3 position;
  simd::float3 normal;
  simd::float4 color;
  simd::float2 textureCoordinate;
};
}
}
