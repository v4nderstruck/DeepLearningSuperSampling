#include "Vertex.hpp"
using namespace x3d::mesh;

Vertex Vertex::create(simd::float3 position, simd::float3 normal, simd::float4 color, simd::float2 textureCoordinate) {
  Vertex vertex;
  vertex.position = position;
  vertex.normal = normal;
  vertex.color = color;
  vertex.textureCoordinate = textureCoordinate;
  return vertex;
}


