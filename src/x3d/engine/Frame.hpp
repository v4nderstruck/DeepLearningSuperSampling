#pragma once
#include <simd/simd.h>
#include <simd/vector_make.h>
#include "../world/Camera.hpp"

namespace x3d {
namespace engine {
using namespace x3d::world::camera;
class Frame {
public:
  simd::float4x4 viewMatrix;
  simd::float4x4 projectionMatrix;
};
}
} // namespace x3d
