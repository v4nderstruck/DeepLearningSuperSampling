#include "Nodes.hpp"

using namespace x3d::world;


void Node::setTranslation(simd::float3 &&position, simd::float3 &&scale, simd::quatf &&rotation) {
  this->position = std::move(position);
  this->scale = std::move(scale);
  this->rotation = std::move(rotation);
}

void Node::render(MTL::RenderCommandEncoder* encoder) {
  if (mesh) {
    mesh->render(encoder);
  }
  for (auto &child : children) {
    child->render(encoder);
  }
}

