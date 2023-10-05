#pragma once
#include "Vertex.hpp"
#include <Metal/Metal.hpp>
#include <iostream>
#include <memory>
#include <simd/simd.h>
namespace x3d {
namespace mesh {

struct RGBAColor {
  float r;
  float g;
  float b;
  float a;

  simd::float4 toFloat4() { return simd::make_float4(r, g, b, a); }
};

class Mesh {
public:
  virtual ~Mesh() {
    std::cout << "[Mesh::~Mesh] destroying a mesh" << std::endl;
  };
  virtual void render(MTL::RenderCommandEncoder *encoder) = 0;
};

template <typename T, typename... Args> class MeshFactory {
public:
  // This is not safe :(
  static std::unique_ptr<T> createMesh(MTL::Device *device, Args &&...args) {
    std::cout << "[MeshFactory::createMesh] creating a mesh" << std::endl;
    return std::make_unique<T>(device, std::forward<Args>(args)...);
  }
};
} // namespace mesh
} // namespace x3d
