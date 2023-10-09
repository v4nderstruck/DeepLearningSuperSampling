#pragma once

#include <GLKit/GLKMatrix4.h>
#include <simd/simd.h>
namespace x3d {
namespace utils {

simd::float4x4 GLKMatrix4ToSimdFloat4x4(GLKMatrix4 &matrix) {
  auto v = simd::float4x4();
  v.columns[0] = simd::make_float4(matrix.m00, matrix.m01, matrix.m02, matrix.m03);
  v.columns[1] = simd::make_float4(matrix.m10, matrix.m11, matrix.m12, matrix.m13);
  v.columns[2] = simd::make_float4(matrix.m20, matrix.m21, matrix.m22, matrix.m23);
  v.columns[3] = simd::make_float4(matrix.m30, matrix.m31, matrix.m32, matrix.m33);
  return std::move(v);
}
}
}

