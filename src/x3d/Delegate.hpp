#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <memory>
#include "engine/Renderer.hpp"

namespace x3d {
class AppDelegate : public NS::ApplicationDelegate {
public:
  ~AppDelegate();

  NS::Menu* createMenuBar();
  virtual void
  applicationWillFinishLaunching(NS::Notification *pNotification) override;
  virtual void
  applicationDidFinishLaunching(NS::Notification *pNotification) override;
  virtual bool applicationShouldTerminateAfterLastWindowClosed(
      NS::Application *pSender) override;

private:
  MTL::Device* pDevice;
  MTK::View* pView;
  NS::Window* pWindow;
  std::unique_ptr<engine::Renderer> pRenderer;
};
} // namespace x3d
