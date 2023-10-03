#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <memory>
#include "engine/Renderer.hpp"
#include "mesh/BasicMeshes.hpp"
#include <future>

namespace x3d {
class AppDelegate : public NS::ApplicationDelegate {
public:
  AppDelegate() {wait = std::promise<void>();}
  NS::Menu* createMenuBar();
  virtual void
  applicationWillFinishLaunching(NS::Notification *pNotification) override;
  virtual void
  applicationDidFinishLaunching(NS::Notification *pNotification) override;
  virtual bool applicationShouldTerminateAfterLastWindowClosed(
      NS::Application *pSender) override;
  x3d::mesh::Cube giveCube();
  void draw();
  std::promise<void> wait;
private:
  NS::SharedPtr<MTK::View> pView;
  NS::SharedPtr<NS::Window> pWindow;
  std::unique_ptr<engine::Renderer> pRenderer;
};
} // namespace x3d
