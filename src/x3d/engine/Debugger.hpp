#pragma once

#include "Metal.hpp"

namespace x3d::engine {
class Debugger {
public:
  static MTL::CaptureManager *createDebugger(MTL::Device *device);
};
} // namespace x3d::engine
