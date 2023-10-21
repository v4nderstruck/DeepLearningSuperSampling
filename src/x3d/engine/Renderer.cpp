#include "Renderer.hpp"
#include "Debugger.hpp"
#include "../world/Nodes.hpp"
#include "Frame.hpp"
#include "Metal.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>

using namespace x3d::engine;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#define FRAME_AVG 30
#define TRIPPLE_FRAME_BUFFERING 3

using namespace x3d::mesh;

Renderer::Renderer(MTL::Device *device, MTK::View *view)
    : MTK::ViewDelegate(), pDevice(NS::TransferPtr(device)), fps(FRAME_AVG),
      frame(0), view(NS::RetainPtr(view)), scene(), 
      frameBuffer(TRIPPLE_FRAME_BUFFERING) {
  pCommandQueue = NS::TransferPtr(pDevice->newCommandQueue());
  std::vector<NS::SharedPtr<MTL::Buffer>> trippleframeBuffers = {
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), MTL::ResourceStorageModeManaged)),
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), MTL::ResourceStorageModeManaged)),
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), MTL::ResourceStorageModeManaged)),
  };
  if (pDevice.get() == nullptr) {
    std::cout << "[Renderer::Renderer] creating device failed" << std::endl;
    exit(1);
  }

  frameBuffer.manageThis(std::move(trippleframeBuffers));
  auto depthDesc = NS::TransferPtr(MTL::DepthStencilDescriptor::alloc()->init());
  depthDesc->setDepthCompareFunction(MTL::CompareFunctionLess);
  depthDesc->setDepthWriteEnabled(true);

  pDepthStencilState = NS::TransferPtr(pDevice->newDepthStencilState(depthDesc.get()));
  
  pLibrary = NS::TransferPtr(mesh::Mesh::BuildShaders(pDevice.get()));
}

Renderer::~Renderer() {}

void Renderer::drawInMTKView(MTK::View *pView) {
  auto now =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  fps.update(now.count());
  frame++;

  NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

  auto debugger = Debugger::createDebugger(pDevice.get());

  MTL::CommandBuffer *pCmd = pCommandQueue->commandBuffer();
  auto uniformBuffer = frameBuffer.nextBuffer();

  Frame* frameUniforms = reinterpret_cast<Frame*>(uniformBuffer->contents());
  /* frameUniforms->resolution = {(int)pView->drawableSize().width, */
  /*                              (int)pView->drawableSize().height}; */

  frameUniforms->viewMatrix = scene.perspectiveCamera.viewMatrix;
  frameUniforms->projectionMatrix = scene.perspectiveCamera.projectionMatrix;

  uniformBuffer->didModifyRange(NS::Range::Make(0, uniformBuffer->length()));


  pCmd->addCompletedHandler(^void(MTL::CommandBuffer *pCmd) {
    frameBuffer.freeBuffer();
  });

  MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();
  pRpd->colorAttachments()->object(0)->setLoadAction(
      MTL::LoadAction::LoadActionClear);
  pRpd->colorAttachments()->object(0)->setClearColor(scene.clearColor);

  MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);
  pEnc->setVertexBuffer(uniformBuffer, 0, ArgumentBufferIndex::UNIFORMS);
  pEnc->setFragmentBuffer(uniformBuffer, 0, ArgumentBufferIndex::UNIFORMS);
  pEnc->setDepthStencilState(pDepthStencilState.get());
  pEnc->setCullMode(MTL::CullModeBack);

  scene.renderScene(pEnc);
  pEnc->endEncoding();
  pCmd->presentDrawable(pView->currentDrawable());
  pCmd->commit();

  debugger->stopCapture();

  pPool->release();


  if (frame % FRAME_AVG == 0) {
    std::cout << "\r"
              << "FPS: " << fps.getFPS() << std::flush;
  }
    exit(1);
}

std::tuple<MTL::PixelFormat, MTL::PixelFormat> Renderer::getPixelFormat() {
  return std::make_tuple(view->colorPixelFormat(),
                         view->depthStencilPixelFormat());
}
