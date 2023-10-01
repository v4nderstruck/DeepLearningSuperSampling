#pragma once

#include "Mesh.hpp"
namespace x3d {
namespace mesh {
class Cube : public Mesh {
public:
  static void create(float width, float height, float depth);
  void render(MTL::RenderCommandEncoder* encoder) override;
};

}
} // namespace x3d
