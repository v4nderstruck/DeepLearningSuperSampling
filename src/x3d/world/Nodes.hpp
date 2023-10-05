#pragma once

#include "../mesh/BasicMeshes.hpp"
#include "../mesh/Mesh.hpp"
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
  Node(Node &&node) = default;
  Node(std::unique_ptr<Mesh>&& mesh, Node *parent, std::string &&name)
      : parent(parent), name(name) { 
    mesh = std::move(mesh);
  }

  void setTranslation(simd::float3 &&position, simd::float3 &&scale,
                      simd::quatf &&rotation);

  template <typename... Args>
  static Node *new_cube(Node *parent, std::string&& name, Args &&...args) {
    std::cout << "[Node::new_cube] creating a cube mesh" << std::endl;
    std::unique_ptr<Cube> cube = Cube::createMesh(std::forward<Args>(args)...);
    std::cout << "[Node::new_cube] creating a cube node" << std::endl;
    auto node = std::make_unique<Node>(std::move(cube), parent, std::move(name));
    std::cout << "[Node::new_cube] move node to parent's children" << std::endl;
    parent->children.push_back(std::move(node));
    std::cout << "[Node::new_cube] returning nodeptr" << std::endl;
    return parent->children.back().get();
  }

private:
  Node *parent;
  std::function<void(Node *, int)> update;
  std::vector<std::unique_ptr<Node>> children;
  simd::float3 position;
  simd::float3 scale;
  simd::quatf rotation;
  std::string name;
  std::unique_ptr<Mesh> mesh;
};

} // namespace world
} // namespace x3d
