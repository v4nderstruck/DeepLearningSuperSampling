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
  Node()
      : position(simd::make_float3(0.0, 0.0, 0.0)),
        scale(simd::make_float3(1.0, 1.0, 1.0)),
        rotation(simd::quatf(0.0, simd::make_float3(1.0, 0, 0))) {}
  Node(std::string &&name) : name(name) {}
  Node(Node &&node) : parent(node.parent), mesh(std::move(node.mesh)){};
  Node(std::unique_ptr<Mesh> &&mesh, Node *parent, std::string &&name)
      : parent(parent), name(name), mesh(std::move(mesh)) {

    std::cout << "[Node::Node] creating a node by moving mesh" << std::endl;
  }

  void setTranslation(simd::float3 &&position, simd::float3 &&scale,
                      simd::quatf &&rotation);

  void rotate(float angle, simd::float3 &&axis);

  void render(MTL::RenderCommandEncoder *encoder,
              simd::float4x4 &parentTransform);

  template <typename... Args>
  static Node *new_cube(Node *parent, std::string &&name, MTL::Device *device,
                        MTL::Library *lib, Args &&...args) {

    std::cout << "[Node::new_cube] creating a cube node" << std::endl;
    auto node = std::make_unique<Node>(
        Cube::createMesh(device, std::forward<Args>(args)...), parent,
        std::move(name));
    std::cout << "[Node::new_cube] cube is at x:" << node->position.x  << " " << node->position.y << " " << node->position.z << std::endl; 
    std::cout << "[Node::new_cube] move node to parent's children" << std::endl;
    parent->children.push_back(std::move(node));
    std::cout << "[Node::new_cube] returning nodeptr" << std::endl;
    return parent->children.back().get();
  }

  std::unique_ptr<Mesh> mesh;
  std::string name;

  std::vector<std::unique_ptr<Node>> children;

private:
  Node *parent;
  std::function<void(Node *, int)> update;
  simd::float3 position;
  simd::float3 scale;
  simd::quatf rotation;
};

} // namespace world
} // namespace x3d
