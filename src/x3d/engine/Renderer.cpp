#include "Renderer.hpp"
#include "Metal.hpp"
#include <chrono>
#include <iostream>
#include <ostream>

using namespace x3d::engine;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#define FRAME_AVG 30

Renderer::Renderer(MTL::Device* device)
    : MTK::ViewDelegate(), pDevice(NS::TransferPtr(device)), fps(FRAME_AVG),
      frame(0) {

  pCommandQueue = NS::TransferPtr(pDevice->newCommandQueue());
}

Renderer::~Renderer() {
  pCommandQueue->release();
}

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
