#include "Camera.hpp"
#include "../utils/helpers.hpp"
#include <cmath>
#include <iostream>
#include <simd/vector_make.h>

using namespace x3d::world::camera;
using namespace x3d::utils;

void Perspective::buildCamera() {
  /* auto p = */
  /*     GLKMatrix4MakePerspective((fov * M_PI) / 180.0, aspectRatio, near, far); */
  /* auto zs = far / (near - far); */
  /* p.m22 = zs; */
  /* p.m32 = zs * near; */
  /* projectionMatrix = GLKMatrix4ToSimdFloat4x4(p); */

  projectionMatrix = makePerspective((fov * M_PI) / 180.0f, aspectRatio, near, far);

  /* auto v = */
  /*     GLKMatrix4MakeLookAt(position.x, position.y, position.z, lookAt.x, */
  /*                          lookAt.y, lookAt.z, up.x, up.y, up.z); */
  /* viewMatrix = GLKMatrix4ToSimdFloat4x4(v); */
  /**/
  /* simd::float4x4 identity = simd::float4x4(); */
  /* identity.columns[0] = simd::make_float4(1, 0, 0, 0); */
  /* identity.columns[1] = simd::make_float4(0, 1, 0, 0); */
  /* identity.columns[2] = simd::make_float4(0, 0, 1, -1.0); */
  /* identity.columns[3] = simd::make_float4(0, 0, 0, 1); */
  /* viewMatrix = identity; */
  /**/

  viewMatrix = makeLookAt(position, lookAt, up);
}

  void Perspective::setInternals(simd::float3 &&position, simd::float3 &&lookAt, simd::float3 &&up,
         float fov, float aspectRatio, float near, float far) {
    this->position = std::move(position);
    this->lookAt = std::move(lookAt);
    this->up = std::move(up);
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->near = near;
    this->far = far;
}
