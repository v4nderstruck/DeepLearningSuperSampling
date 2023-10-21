#pragma once

#include "../mesh/BasicMeshes.hpp"
#include "../world/Scene.hpp"
#include "Buffering.hpp"
#include "FPS.hpp"
#include "MetalKit/MTKView.hpp"
#include <Metal/Metal.hpp>
#include <thread>
#include <tuple>

namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device *device, MTK::View *view);
  virtual ~Renderer() override;
  virtual void drawInMTKView(MTK::View *pView) override;

  NS::SharedPtr<MTL::Device> pDevice;
  NS::SharedPtr<MTL::Library> pLibrary;
  std::tuple<MTL::PixelFormat, MTL::PixelFormat> getPixelFormat();

  x3d::world::Scene scene;
private:
  FPS fps;
  NS::SharedPtr<MTL::DepthStencilState> pDepthStencilState;
  NS::SharedPtr<MTL::CommandQueue> pCommandQueue;
  NS::SharedPtr<MTK::View> view;
  BufferManager frameBuffer;
  int frame;
};
} // namespace engine
} // namespace x3d
