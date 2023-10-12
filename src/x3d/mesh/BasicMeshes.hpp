#pragma once
#include "Mesh.hpp"
#include "Metal.hpp"
#include <iostream>
namespace x3d {
namespace mesh {

class Cube : public Mesh, public MeshFactory<Cube, float, float, float, RGBAColor> {
public:
  enum FillMode { Fill, Wireframe };
  Cube(MTL::Device* device, float width, float height, float depth, RGBAColor color);
  Cube(Cube&& other) = default;
  ~Cube() override  {
    std::cout << "[Cube::~Cube] destroying a cube" << std::endl;
  }
  void render(MTL::RenderCommandEncoder *encoder) override;
  void BuildVertexDescriptor() override;

private:
  NS::SharedPtr<MTL::RenderPipelineState> renderPipelineState;
  NS::SharedPtr<MTL::Buffer> vertexBuffer;
  long vertexCount;
};
} // namespace mesh
} // namespace x3d
