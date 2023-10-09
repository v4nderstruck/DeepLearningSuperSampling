#pragma once

#include <simd/simd.h>
#include <GLKit/GLKMatrix4.h>

namespace x3d {
namespace world {
namespace camera {
class Perspective {
public:
  Perspective() = default;
  Perspective(simd::float3 &&position, simd::float3 &&lookAt, simd::float3 &&up,
         float fov, float aspectRatio, float near, float far)
      : position(position), lookAt(lookAt), up(up), fov(fov),
        aspectRatio(aspectRatio), near(near), far(far) {}
  void setInternals(simd::float3 &&position, simd::float3 &&lookAt, simd::float3 &&up,
         float fov, float aspectRatio, float near, float far) {
    position = position;
    lookAt = lookAt;
    up = up;
    fov = fov;
    aspectRatio = aspectRatio;
    near = near;
    far = far;
  }
  void buildCamera();

private:
  simd::float3 position;
  simd::float3 lookAt;
  simd::float3 up;
  float fov;
  float aspectRatio;
  float near;
  float far;

  simd::float4x4 projectionMatrix;
  simd::float4x4 viewMatrix;
};
} // namespace perspective
} // namespace world
} // namespace x3d
