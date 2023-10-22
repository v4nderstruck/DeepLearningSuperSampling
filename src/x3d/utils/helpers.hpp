#pragma once

#include <GLKit/GLKMatrix4.h>
#include <simd/simd.h>
namespace x3d {
namespace utils {
simd::float4x4 makePerspective(float fovRadians, float aspect, float znear,
                               float zfar) {
  using simd::float4;
  float ys = 1.f / tanf(fovRadians * 0.5f);
  float xs = ys / aspect;
  float zs = zfar / (zfar - znear);
  return simd_matrix(
      (float4){xs, 0.0f, 0.0f, 0.0f}, (float4){0.0f, ys, 0.0f, 0.0f},
      (float4){0.0f, 0.0f, zs, 1.0f}, (float4){0, 0, -znear * zs, 0});
}

simd::float4x4 makeLookAt(simd::float3 &eye, simd::float3 &center,
                          simd::float3 &up) {
  using simd::float4;
  simd::float3 zAxis = simd_normalize(center-eye);
  simd::float3 xAxis = simd_normalize(simd_cross(up, zAxis));
  simd::float3 yAxis = simd_cross(zAxis, xAxis);

  return simd_matrix(
    (float4) {xAxis.x, yAxis.x, zAxis.x, 0.0},
    (float4) {xAxis.y, yAxis.y, zAxis.y, 0.0},
    (float4) {xAxis.z, yAxis.z, zAxis.z, 0.0},
    (float4) {-simd_dot(xAxis, eye), -simd_dot(yAxis, eye), -simd_dot(zAxis, eye), 1.0}
  );
}

simd::float4x4 GLKMatrix4ToSimdFloat4x4(GLKMatrix4 &matrix) {
  return simd_matrix_from_rows(
      (simd::float4){matrix.m00, matrix.m01, matrix.m02, matrix.m03},
      (simd::float4){matrix.m10, matrix.m11, matrix.m12, matrix.m13},
      (simd::float4){matrix.m20, matrix.m21, matrix.m22, matrix.m23},
      (simd::float4){matrix.m30, matrix.m31, matrix.m32, matrix.m33});
}
} // namespace utils
} // namespace x3d
