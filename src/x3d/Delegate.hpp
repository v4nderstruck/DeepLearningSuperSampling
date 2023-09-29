#pragma once

#include <cassert>
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <memory>

namespace x3d {
class AppDelegate {
public:
  AppDelegate();
  ~AppDelegate();

private:
};
} // namespace x3d
