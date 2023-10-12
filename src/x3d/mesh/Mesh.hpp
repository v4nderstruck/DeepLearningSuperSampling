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
  // TODO: Implement basic render here
  void UpdateRenderPipelineState(MTL::RenderCommandEncoder *enconder);
  void BuildRenderPipelineState(MTL::Device *device, MTL::PixelFormat color, MTL::PixelFormat stencil);


  virtual void BuildVertexDescriptor() = 0;
  static MTL::Library* BuildShaders(MTL::Device* device);
  NS::SharedPtr<MTL::VertexDescriptor> _vertexDescriptor;
private:
  NS::SharedPtr<MTL::Function> _vertexFn;
  NS::SharedPtr<MTL::Function> _fragmentFn;
  NS::SharedPtr<MTL::RenderPipelineState> _renderPipelineState;

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
