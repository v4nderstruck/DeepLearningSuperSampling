#pragma once

#include "Camera.hpp"
#include "Metal.hpp"
#include "Nodes.hpp"
namespace x3d {
namespace world {

class Scene {
public:
  Scene();
  void renderScene(MTL::RenderCommandEncoder* encoder);


  MTL::ClearColor clearColor;
  Node root;
  camera::Perspective perspectiveCamera;
};
}
} // namespace x3d
