#pragma once
#include <Metal/Metal.hpp>
#include <simd/simd.h>
#include <iostream>
#include "Vertex.hpp"
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
  virtual void render(MTL::RenderCommandEncoder *encoder) = 0;
};

template <typename T, typename... Args> class MeshFactory {
public:
  // This is not safe :(
  static T createMesh(MTL::Device* device, Args&&... args) { 
    std::cout << "MeshFactory::createMesh" << std::endl;
    return T::create(device, std::forward<Args>(args)...); 
  }
};
} // namespace mesh
} // namespace x3d
