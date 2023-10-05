#pragma once

#include "FPS.hpp"
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <thread>
#include "../mesh/BasicMeshes.hpp"
#include "MetalKit/MTKView.hpp"

namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device* device, MTK::View* view);
  virtual ~Renderer() override;
  virtual void drawInMTKView(MTK::View *pView) override;

  void buildShaders();

  x3d::mesh::Cube giveCube();

private:
  FPS fps;
  NS::SharedPtr<MTL::Device> pDevice;
  NS::SharedPtr<MTL::Library> library;
  NS::SharedPtr<MTL::CommandQueue> pCommandQueue;
  NS::SharedPtr<MTK::View> view;
  // FIXME: move render state to rendering a mesh
  NS::SharedPtr<MTL::RenderPipelineState> pipelineState;
  int frame;
};
} // namespace engine
} // namespace x3d
