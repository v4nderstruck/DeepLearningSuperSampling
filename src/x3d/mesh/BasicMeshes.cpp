#include "BasicMeshes.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <simd/vector_make.h>

using namespace x3d::mesh;

Cube::Cube(MTL::Device *device, float width, float height, float depth,
            RGBAColor color)
    {

  std::cout << "[Cube] create cube" << std::endl;
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

  std::cout << "[Cube] created vertices: " << vertices.size() << std::endl;
  vertexBuffer = Vertex::toBuffer(device, vertices);
  vertexCount = vertices.size();
}

Cube Cube::create(MTL::Device *device, float width, float height, float depth,
            RGBAColor color) {
  // a cube as 6 faces, each face has 2 triangles, each triangle has 3 vertices
  // = 6 * 2 * 3 = 36 vertices
  std::cout << "[Cube] create cube" << std::endl;
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

  /* std::cout << "[Cube] created vertices: " << vertices.size() << std::endl; */
  /* auto buffer = Vertex::toBuffer(device, vertices); */
  /* Cube c(buffer, vertices.size()); */
  /* return c; */
}

void Cube::render(MTL::RenderCommandEncoder *encoder) { return; }
