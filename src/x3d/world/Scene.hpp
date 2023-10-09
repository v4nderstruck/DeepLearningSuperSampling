#pragma once

#include "Camera.hpp"
#include "Metal.hpp"
#include "Nodes.hpp"
namespace x3d {
namespace world {
using namespace x3d::mesh;
using namespace camera;
class Scene {

  Scene();

  void renderScene(MTL::RenderCommandEncoder* encoder);


private:
  Node root;
  Perspective perspectiveCamera;
};
}
} // namespace x3d
