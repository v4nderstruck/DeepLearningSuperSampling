#pragma once

#include "../mesh/BasicMeshes.hpp"
#include "../mesh/Mesh.hpp"
#include "Metal.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <simd/simd.h>
#include <vector>

namespace x3d {
namespace world {

using namespace x3d::mesh;
class Node {
public:
  Node(std::string &&name) : name(name) {}
  Node(Node &&node) : parent(node.parent), mesh(std::move(node.mesh)){};
  Node(std::unique_ptr<Mesh> &&mesh, Node *parent, std::string &&name)
      : parent(parent), name(name), mesh(std::move(mesh)) {

    std::cout << "[Node::Node] creating a node by moving mesh" << std::endl;
  }

  void setTranslation(simd::float3 &&position, simd::float3 &&scale,
                      simd::quatf &&rotation);

  void render(MTL::RenderCommandEncoder *encoder,
              simd::float4x4 &parentTransform);

  template <typename... Args>
  static Node *new_cube(Node *parent, std::string &&name, MTL::Device *device,
                        MTL::Library *lib, Args &&...args) {
    std::cout << "[Node::new_cube] creating a cube mesh" << std::endl;
    /* cube->BuildRenderPipelineState(device, lib,
       MTL::PixelFormat::PixelFormatBGRA8Unorm,
       MTL::PixelFormat::PixelFormatDepth16Unorm); */
    std::cout << "[Node::new_cube] creating a cube node" << std::endl;
    auto node = std::make_unique<Node>(
        Cube::createMesh(device, std::forward<Args>(args)...), parent,
        std::move(name));
    std::cout << "[Node::new_cube] move node to parent's children" << std::endl;
    parent->children.push_back(std::move(node));
    std::cout << "[Node::new_cube] returning nodeptr" << std::endl;
    return parent->children.back().get();
  }

  std::unique_ptr<Mesh> mesh;
  std::string name;

private:
  Node *parent;
  std::function<void(Node *, int)> update;
  std::vector<std::unique_ptr<Node>> children;
  simd::float3 position;
  simd::float3 scale;
  simd::quatf rotation;
};

} // namespace world
} // namespace x3d
