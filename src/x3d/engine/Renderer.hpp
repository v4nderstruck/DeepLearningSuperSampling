#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include "FPS.hpp"
namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device* device);
  virtual ~Renderer() override;
  virtual void drawInMTKView(MTK::View *pView) override;
private:

  FPS fps;
  NS::SharedPtr<MTL::Device> pDevice;
  NS::SharedPtr<MTL::CommandQueue> pCommandQueue;
  int frame;
};
} // namespace engine
} // namespace x3d
