#pragma once

#include "FPS.hpp"
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <thread>
#include "../mesh/BasicMeshes.hpp"

namespace x3d {
namespace engine {
class Renderer : public MTK::ViewDelegate {
public:
  Renderer(MTL::Device* device);
  virtual ~Renderer() override;
  virtual void drawInMTKView(MTK::View *pView) override;

  x3d::mesh::Cube giveCube();

private:
  FPS fps;
  NS::SharedPtr<MTL::CommandQueue> pCommandQueue;
  MTL::Device* pDevice;
  int frame;
};
} // namespace engine
} // namespace x3d
