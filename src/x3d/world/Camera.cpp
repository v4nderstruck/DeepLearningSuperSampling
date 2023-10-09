#include "Camera.hpp"
#include "../utils/helpers.hpp"
#include <cmath>

using namespace x3d::world::camera;
using namespace x3d::utils;

void Perspective::buildCamera() {
  auto p =
      GLKMatrix4MakePerspective((fov * M_PI) / 180.0, aspectRatio, near, far);
  projectionMatrix = GLKMatrix4ToSimdFloat4x4(p);

  auto tartet = position + lookAt;
  auto v =
      GLKMatrix4MakeLookAt(position.x, position.y, position.z, tartet.x,
                           tartet.y, tartet.z, up.x, up.y, up.z);
  viewMatrix = GLKMatrix4ToSimdFloat4x4(v);

}
