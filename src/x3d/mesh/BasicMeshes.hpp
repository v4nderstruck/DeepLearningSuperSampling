#pragma once
#include "Mesh.hpp"
namespace x3d {
namespace mesh {

class Cube : public Mesh, public MeshFactory<Cube, float, float, float, RGBAColor> {
public:
  enum FillMode { Fill, Wireframe };
  Cube(MTL::Device* device, float width, float height, float depth, RGBAColor color);
  static Cube create(MTL::Device* device, float width, float height, float depth, RGBAColor color);
  void render(MTL::RenderCommandEncoder *encoder) override;
private:
  NS::SharedPtr<MTL::Buffer> vertexBuffer;
  long vertexCount;
};
} // namespace mesh
} // namespace x3d
