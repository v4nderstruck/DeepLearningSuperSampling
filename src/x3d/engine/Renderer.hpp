#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device *device);
  virtual ~Renderer() override;
  virtual void drawInMTKView(MTK::View *pView) override;
private:
  MTL::Device* pDevice;
  MTL::CommandQueue* pCommandQueue;
};
} // namespace engine
} // namespace x3d
