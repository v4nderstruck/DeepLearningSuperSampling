#include "Renderer.hpp"
#include "Metal.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
#include <simd/vector_make.h>

using namespace x3d::engine;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#define FRAME_AVG 30

using namespace x3d::mesh;

Renderer::Renderer(MTL::Device* device)
    : MTK::ViewDelegate(), pDevice(device), fps(FRAME_AVG),
      frame(0) {
  pCommandQueue = NS::TransferPtr(pDevice->newCommandQueue());
}

Renderer::~Renderer() {  }

void Renderer::drawInMTKView(MTK::View *pView) {
  auto now =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  fps.update(now.count());
  frame++;

  NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

  MTL::CommandBuffer *pCmd = pCommandQueue->commandBuffer();
  MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();
  MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);
  pEnc->endEncoding();
  pCmd->presentDrawable(pView->currentDrawable());
  pCmd->commit();

  pPool->release();

  if (frame % FRAME_AVG == 0) {
    std::cout << "\r"
              << "FPS: " << fps.getFPS() << std::flush;
  }
}
x3d::mesh::Cube Renderer::giveCube() {
  std::cout << "[Renderer::giveCube] make vertex" << std::endl;
  auto v = Vertex::create(
      simd::make_float3(1.0, 1.0, 1.0), simd::make_float3(0.0, 0.0, 0.0),
      simd::make_float4(1.0, 1.0, 0.0, 1.0), simd::make_float2(1.0, 0.0));
  std::cout << "[Renderer::giveCube] make buffer" << std::endl;
  if (pDevice == nullptr) {
    std::cout << "[Renderer::giveCube] pDevice is nullptr" << std::endl;
  }
  auto b = pDevice->newBuffer(sizeof(Vertex), MTL::ResourceStorageModeManaged);
  std::cout << "[Renderer::giveCube] memcpy" << std::endl;
  memcpy(b->contents(), &v, sizeof(Vertex));

  std::cout << "[Renderer::giveCube] try make cube" << std::endl;
  return Cube(pDevice, 1.0, 1.0, 1.0, RGBAColor{1.0, 1.0, 0.0, 1.0});
}
