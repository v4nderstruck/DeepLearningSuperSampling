#include "Vertex.hpp"
#include "Metal.hpp"
#include <iostream>

using namespace x3d::mesh;

Vertex Vertex::create(simd::float3 position, simd::float3 normal,
                      simd::float4 color, simd::float2 textureCoordinate) {
  Vertex vertex;
  vertex.position = position;
  vertex.normal = normal;
  vertex.color = color;
  vertex.textureCoordinate = textureCoordinate;
  return vertex;
}

NS::SharedPtr<MTL::Buffer> Vertex::toBuffer(MTL::Device *device,
                                            std::vector<Vertex> &vertices) {
  return NS::TransferPtr(
      device->newBuffer(vertices.data(), sizeof(Vertex) * vertices.size(), {}));
}

void Vertex::debug_size() {
  std::cout << "sizeof(Vertex): " << sizeof(*this) << std::endl;
  std::cout << "sizeof(simd::float2)texture: " << sizeof(textureCoordinate)
            << std::endl;
  std::cout << "sizeof(simd::float3)position: " << sizeof(position)
            << std::endl;
  std::cout << "sizeof(simd::float3)normal: " << sizeof(normal) << std::endl;
  std::cout << "sizeof(simd::float4)color: " << sizeof(color) << std::endl;
  std::cout << "alignof(Vertex): " << alignof(*this) << std::endl;
}
