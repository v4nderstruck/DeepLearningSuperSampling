
#include "Renderer.hpp"

using namespace x3d::engine;

Renderer::Renderer(MTL::Device *device)
    : MTK::ViewDelegate(), pDevice(device->retain()) {
  pCommandQueue = pDevice->newCommandQueue();
}

Renderer::~Renderer() {
  pCommandQueue->release();
  pDevice->release();
}

void Renderer::drawInMTKView(MTK::View *pView) {
  NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

  MTL::CommandBuffer *pCmd = pCommandQueue->commandBuffer();
  MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();
  MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);
  pEnc->endEncoding();
  pCmd->presentDrawable(pView->currentDrawable());
  pCmd->commit();

  pPool->release();
}
