#include "Renderer.hpp"
#include "../world/Nodes.hpp"
#include "Frame.hpp"
#include "Metal.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
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
      frame(0), view(NS::RetainPtr(view)), frameBuffer(3) {
  pCommandQueue = NS::TransferPtr(pDevice->newCommandQueue());
  buildShaders();
  // FIXME: missing proper buffer content!!
  std::vector<NS::SharedPtr<MTL::Buffer>> trippleframeBuffers = {
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), {})),
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), {})),
      NS::TransferPtr(pDevice->newBuffer(sizeof(Frame), {})),
  };

  frameBuffer.manageThis(std::move(trippleframeBuffers));
}

Renderer::~Renderer() {}

void Renderer::buildShaders() {
  // pipeline vertices -> vertex -> raster -> fragment -> pixel
  const char *shader = R"(
    #include <metal_stdlib>
    using namespace metal;
    
    struct VertexIn {
      float3 position [[attribute(0)]];
      float3 normal [[attribute(1)]];
      float4 color [[attribute(2)]];
      float2 textureCoordinate [[attribute(3)]];
    };
    
    struct VertexOut {
      float4 position [[position]];
      float4 color;
      float2 tex;
    };

    struct Uniforms {
      int2 resolution;
      float4x4 viewMatrix;
      float4x4 projectionMatrix;
    };

    struct ModelUniforms {
      float4x4 modelMatrix;
    };

    vertex VertexOut vertex_vertices(
      const VertexIn vertex_array [[stage_in]], 
      const device Uniforms& uniforms [[buffer(0)]], 
      const device ModelUniforms& model_uniforms [[buffer(1)]]
    ) {
      VertexOut out;
      out.position = uniforms.projectionMatrix * uniforms.viewMatrix * model_uniforms.modelMatrix * float4(vertex_array.position, 1.0);
      out.color = vertex_array.color;
      out.tex = vertex_array.textureCoordinate;
      return out;
    }
   
    fragment float4 fragment_color(
      VertexOut in [[stage_in]]
    ) {
      return in.color;
    }
    
  )";
  NS::Error *error = nullptr;
  library = NS::TransferPtr(pDevice->newLibrary(
      NS::String::string(shader, NS::StringEncoding::UTF8StringEncoding),
      nullptr, &error));
  if (library.get() == nullptr) {
    std::cout << "[Renderer::buildShaders] Error building shader: "
              << error->localizedDescription()->utf8String() << std::endl;
    exit(1);
  }

  auto vertexFunc = NS::TransferPtr(library->newFunction(NS::String::string(
      "vertex_vertices", NS::StringEncoding::UTF8StringEncoding)));
  auto fragmentFunc = NS::TransferPtr(library->newFunction(NS::String::string(
      "fragment_color", NS::StringEncoding::UTF8StringEncoding)));

  // FIXME: For now only set the shader functions here!
  auto descriptor =
      NS::TransferPtr(MTL::RenderPipelineDescriptor::alloc()->init());
  descriptor->colorAttachments()->object(0)->setPixelFormat(
      view->colorPixelFormat());
  descriptor->setDepthAttachmentPixelFormat(view->depthStencilPixelFormat());
  descriptor->setVertexFunction(vertexFunc.get());
  descriptor->setFragmentFunction(fragmentFunc.get());

  // FIXME: Proper VertexDescriptor needed, this is only for test
  auto vertexDescriptor =
      NS::TransferPtr(MTL::VertexDescriptor::alloc()->init());

  vertexDescriptor->attributes()->object(0)->setFormat(
      MTL::VertexFormat::VertexFormatFloat3);
  vertexDescriptor->attributes()->object(0)->setBufferIndex(0);
  vertexDescriptor->attributes()->object(0)->setOffset(0);

  std::cout << "sizeof(simd::float3): " << sizeof(simd::float3) << std::endl;
  vertexDescriptor->attributes()->object(1)->setFormat(
      MTL::VertexFormat::VertexFormatFloat3);
  vertexDescriptor->attributes()->object(1)->setBufferIndex(0);
  vertexDescriptor->attributes()->object(1)->setOffset(sizeof(simd::float3));

  vertexDescriptor->attributes()->object(2)->setFormat(
      MTL::VertexFormat::VertexFormatFloat4);
  vertexDescriptor->attributes()->object(2)->setBufferIndex(0);
  vertexDescriptor->attributes()->object(2)->setOffset(sizeof(simd::float3) +
                                                       sizeof(simd::float3));

  vertexDescriptor->attributes()->object(3)->setFormat(
      MTL::VertexFormat::VertexFormatFloat2);
  vertexDescriptor->attributes()->object(3)->setBufferIndex(0);
  vertexDescriptor->attributes()->object(3)->setOffset(
      sizeof(simd::float3) + sizeof(simd::float3) + sizeof(simd::float4));

  vertexDescriptor->layouts()->object(0)->setStride(sizeof(Vertex));

  descriptor->setVertexDescriptor(vertexDescriptor.get());

  pipelineState = NS::TransferPtr(
      pDevice->newRenderPipelineState(descriptor.get(), &error));

  if (pipelineState.get() == nullptr) {
    std::cout << "[Renderer::buildShaders] Error setting renderPipeline: "
              << error->localizedDescription()->utf8String() << std::endl;
    exit(1);
  }
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
void Renderer::giveCube() {
  using namespace x3d::world;
  std::cout << "[Renderer::giveCube] make root" << std::endl;
  Node n(std::move(std::string("root")));
  std::cout << "[Renderer::giveCube] make cube at parent" << std::endl;
  Node* actual_cube = Node::new_cube(&n, std::string("cube"), pDevice.get(), 1.0, 1.0, 1.0,
                                    RGBAColor{1.0, 1.0, 0.0, 1.0});
  std::cout << "[Renderer::giveCube] make cube done " << std::hex << (void*)actual_cube << std::endl;
}
