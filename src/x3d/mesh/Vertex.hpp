#pragma once
#include <simd/simd.h>
#include <Metal/Metal.hpp>

namespace x3d {
namespace mesh {
class Vertex {
  static Vertex create(simd::float3 position, simd::float3 normal, simd::float4 color, simd::float2 textureCoordinate);
  NS::SharedPtr<MTL::Buffer> getBuffer();
private:  
  simd::float2 textureCoordinate;
  simd::float3 position;
  simd::float3 normal;
  simd::float4 color;
};
}
}
