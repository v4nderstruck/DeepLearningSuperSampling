#pragma once

#include <simd/simd.h>
#include <GLKit/GLKMatrix4.h>

namespace x3d {
namespace world {
namespace camera {
class Perspective {
public:
  Perspective() = default;

  void setInternals(simd::float3 &&position, simd::float3 &&lookAt, simd::float3 &&up,
         float fov, float aspectRatio, float near, float far);

  void buildCamera();

  simd_float4x4 projectionMatrix;
  simd_float4x4 viewMatrix;
private:
  simd::float3 position;
  simd::float3 lookAt;
  simd::float3 up;
  float fov;
  float aspectRatio;
  float near;
  float far;

};
} // namespace perspective
} // namespace world
} // namespace x3d
