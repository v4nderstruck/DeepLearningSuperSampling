#include "BasicMeshes.hpp"
#include "../engine/Buffering.hpp"
#include "Metal.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <ostream>
#include <simd/vector_make.h>

using namespace x3d::mesh;

Cube::Cube(MTL::Device *device, float width, float height, float depth,
           RGBAColor color) {
  float halfWidth = width / 2.0;
  float halfHeight = height / 2.0;
  float halfDepth = depth / 2.0;
  auto colorfloat4 = color.toFloat4();

  std::vector<Vertex> vertices = {
      // Top Face
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      // Right Face
      Vertex::create(simd::make_float3(halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      // Left Face
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      // Front face
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      // Back face
      Vertex::create(simd::make_float3(-halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      // Bottom Face
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 0.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 1.0)),
      Vertex::create(simd::make_float3(-halfWidth, -halfHeight, -halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(0.0, 1.0)),
      Vertex::create(simd::make_float3(halfWidth, -halfHeight, halfDepth),
                     simd::make_float3(0.0, 0.0, 0.0), colorfloat4,
                     simd::make_float2(1.0, 0.0))};

  std::cout << "[Cube::Cube] created cube " << std::endl;
  vertexBuffer = Vertex::toBuffer(device, vertices);
  vertexCount = vertices.size();
}

void Cube::BuildVertexDescriptor() {
  _vertexDescriptor =
      NS::TransferPtr(MTL::VertexDescriptor::alloc()->init());

  _vertexDescriptor->attributes()->object(0)->setFormat(
      MTL::VertexFormat::VertexFormatFloat3);
  _vertexDescriptor->attributes()->object(0)->setBufferIndex(x3d::engine::ArgumentBufferIndex::VERTICES);
  _vertexDescriptor->attributes()->object(0)->setOffset(0);

  _vertexDescriptor->attributes()->object(1)->setFormat(
      MTL::VertexFormat::VertexFormatFloat3);
  _vertexDescriptor->attributes()->object(1)->setBufferIndex(x3d::engine::ArgumentBufferIndex::VERTICES);
  _vertexDescriptor->attributes()->object(1)->setOffset(sizeof(simd::float3));

  _vertexDescriptor->attributes()->object(2)->setFormat(
      MTL::VertexFormat::VertexFormatFloat4);
  _vertexDescriptor->attributes()->object(2)->setBufferIndex(x3d::engine::ArgumentBufferIndex::VERTICES);
  _vertexDescriptor->attributes()->object(2)->setOffset(sizeof(simd::float3) +
                                                       sizeof(simd::float3));

  _vertexDescriptor->attributes()->object(3)->setFormat(
      MTL::VertexFormat::VertexFormatFloat2);
  _vertexDescriptor->attributes()->object(3)->setBufferIndex(x3d::engine::ArgumentBufferIndex::VERTICES);
  _vertexDescriptor->attributes()->object(3)->setOffset(
      sizeof(simd::float3) + sizeof(simd::float3) + sizeof(simd::float4));

  _vertexDescriptor->layouts()->object(0)->setStride(sizeof(Vertex));
  
}


void Cube::render(MTL::RenderCommandEncoder *encoder) {
  encoder->setVertexBuffer(vertexBuffer.get(), 0,
                           x3d::engine::ArgumentBufferIndex::VERTICES);
  encoder->setTriangleFillMode(MTL::TriangleFillMode::TriangleFillModeFill);
  encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, 0, vertexCount, 1);
}
