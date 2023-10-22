#include "Nodes.hpp"
#include "../engine/Buffering.hpp"
#include <simd/matrix_types.h>
#include <simd/quaternion.h>
#include <simd/vector_make.h>

using namespace x3d::world;

void Node::setTranslation(simd::float3 &&position, simd::float3 &&scale,
                          simd::quatf &&rotation) {
  this->position = std::move(position);
  this->scale = std::move(scale);
  this->rotation = std::move(rotation);
}

void Node::render(MTL::RenderCommandEncoder *encoder,
                  simd::float4x4 &parentTransform) {
  auto posTransform = simd::float4x4();

  posTransform.columns[0] = simd::make_float4(1, 0, 0, 0);
  posTransform.columns[1] = simd::make_float4(0, 1, 0, 0);
  posTransform.columns[2] = simd::make_float4(0, 0, 1, 0);
  posTransform.columns[3] = simd::make_float4(position, 1);

  auto rotTransform = simd::quatf(0.0, simd::make_float3(1.0, 0.0, 0.0));
  posTransform = matrix_identity_float4x4;

  if (mesh) {
    encoder->setVertexBytes(&posTransform, sizeof(simd::float4x4),
                            x3d::engine::ArgumentBufferIndex::MODELS);
    mesh->UpdateRenderPipelineState(encoder);
    mesh->render(encoder);
  }
  for (auto &child : children) {
    child->render(encoder, posTransform);
  }
}
