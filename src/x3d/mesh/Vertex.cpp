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
  auto buffer = device->newBuffer(sizeof(Vertex) * vertices.size(),
                                  MTL::ResourceStorageModeManaged);
  memcpy(buffer->contents(), vertices.data(), sizeof(Vertex) * vertices.size());
  buffer->didModifyRange(NS::Range(0, buffer->length()));
  return NS::TransferPtr(buffer);
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
