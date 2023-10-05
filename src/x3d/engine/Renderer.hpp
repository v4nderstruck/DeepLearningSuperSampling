#pragma once

#include "../mesh/BasicMeshes.hpp"
#include "Buffering.hpp"
#include "FPS.hpp"
#include "MetalKit/MTKView.hpp"
#include <Metal/Metal.hpp>
#include <thread>

namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device *device, MTK::View *view);
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
  BufferManager frameBuffer;
  int frame;
};
} // namespace engine
} // namespace x3d
