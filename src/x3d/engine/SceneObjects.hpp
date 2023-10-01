#pragma once

#include <simd/simd.h>
#include <vector>

namespace x3d {
namespace engine {
class Node {
public:
  simd::float4 getTranslate();
  void renderNode();
private:
  simd::float3 positionTranslate;
  simd::float3 scaleTranslate;
  simd::float4 rotationTranslate;
};

class Scene {
public:
  void renderFlatScene();
private:
  Node world;
  std::vector<Node> flatScene;
};
}
} // namespace x3d
