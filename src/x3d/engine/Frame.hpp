#pragma once
#include <simd/simd.h>
#include <simd/vector_make.h>

namespace x3d {
namespace engine {
class Frame {
public:
  simd::int2 resolution;
  simd::float4x4 viewMatrix;
  simd::float4x4 projectionMatrix;
};
}
} // namespace x3d
