#include "Mesh.hpp"
#include "Metal.hpp"
#include <cstddef>
#include <iostream>

using namespace x3d::mesh;

MTL::Library *Mesh::BuildShaders(MTL::Device *device) {
  const char *shader = R"(
  #include <metal_stdlib>
  using namespace metal;
  
  struct VertexIn {
    float3 position;
    float3 normal;
    float4 color;
    float2 textureCoordinate;
  };
  
  struct VertexOut {
    float4 position [[position]];
    float4 color;
    float2 tex;

  };

  struct Uniforms {
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
  };

  struct ModelUniforms {
    float4x4 modelMatrix;
  };

  struct FragmentOut {
  float4 color [[color(0)]];
  };

  vertex VertexOut vertex_vertices(
    const device VertexIn* vertex_array [[buffer(0)]], 
    const device Uniforms& uniforms [[buffer(1)]], 
    const device ModelUniforms& model_uniforms [[buffer(2)]],
    uint vertexId [[vertex_id]]
  ) {
    VertexOut out;
    float4 pos = float4(vertex_array[vertexId].position, 1.0);
    float4x4 mvp = uniforms.projectionMatrix * model_uniforms.modelMatrix;
    pos = mvp * pos;
    out.position = pos; 
    out.color = vertex_array[vertexId].color;
    out.tex = vertex_array[vertexId].textureCoordinate;
    return out;
  }
 
  fragment FragmentOut fragment_color(
    VertexOut in [[stage_in]]
  ) {
    FragmentOut  out;
    out.color = in.color;
    return out;
  }
  
)";
  NS::Error *error = nullptr;
  MTL::Library *lib = device->newLibrary(
      NS::String::string(shader, NS::StringEncoding::UTF8StringEncoding),
      nullptr, &error);
  if (lib == nullptr) {
    std::cout << "[Mesh::BuildShaders] Error building library: "
              << error->localizedDescription()->utf8String() << std::endl;
    exit(1);
  }
  return lib;
}

void Mesh::BuildRenderPipelineState(MTL::Device *device, MTL::Library *lib,
                                    MTL::PixelFormat color,
                                    MTL::PixelFormat stencil) {
  BuildVertexDescriptor();

  std::cout << "[Mesh::BuildRenderPipelineState] building render pipeline "
               "descriptor"
            << std::endl;
  auto descriptor =
      NS::TransferPtr(MTL::RenderPipelineDescriptor::alloc()->init());
  descriptor->colorAttachments()->object(0)->setPixelFormat(color);
  descriptor->setDepthAttachmentPixelFormat(stencil);

  auto vertexFn = NS::TransferPtr(lib->newFunction(
      NS::String::string("vertex_vertices", NS::StringEncoding::UTF8StringEncoding)));
  auto fragmentFn = NS::TransferPtr(lib->newFunction(
      NS::String::string("fragment_color", NS::StringEncoding::UTF8StringEncoding)));

  descriptor->setVertexFunction(vertexFn.get());
  descriptor->setFragmentFunction(fragmentFn.get());
  //  descriptor->setVertexDescriptor(_vertexDescriptor.get());


  std::cout << "[Mesh::BuildRenderPipelineState] building render pipeline "
               "state"
            << std::endl;
  NS::Error *error = nullptr;
  _renderPipelineState =
      NS::TransferPtr(device->newRenderPipelineState(descriptor.get(), &error));

  if (_renderPipelineState.get() == nullptr) {
    std::cout << "[Mesh::BuildRenderPipelineState] Error building render "
                 "pipeline state: "
              << error->localizedDescription()->utf8String() << std::endl;
    exit(1);
  }
}

void Mesh::UpdateRenderPipelineState(MTL::RenderCommandEncoder *encoder) {
  encoder->setRenderPipelineState(_renderPipelineState.get());
}
