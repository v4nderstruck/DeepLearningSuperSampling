#include "Delegate.hpp"
#include "Metal.hpp"
#include "engine/Renderer.hpp"
#include "mesh/BasicMeshes.hpp"
#include <iostream>

#include <chrono>
#include <thread>
using namespace x3d;

NS::Menu *AppDelegate::createMenuBar() {
  std::cout << "[AppDelegate::createMenuBar] create bar" << std::endl;
  using NS::StringEncoding::UTF8StringEncoding;

  NS::Menu *pMainMenu = NS::Menu::alloc()->init();
  NS::MenuItem *pAppMenuItem = NS::MenuItem::alloc()->init();
  NS::Menu *pAppMenu = NS::Menu::alloc()->init(
      NS::String::string("Appname", UTF8StringEncoding));

  NS::String *appName =
      NS::RunningApplication::currentApplication()->localizedName();
  NS::String *quitItemName = NS::String::string("Quit ", UTF8StringEncoding)
                                 ->stringByAppendingString(appName);
  SEL quitCb = NS::MenuItem::registerActionCallback(
      "appQuit", [](void *, SEL, const NS::Object *pSender) {
        auto pApp = NS::Application::sharedApplication();
        pApp->terminate(pSender);
      });

  NS::MenuItem *pAppQuitItem = pAppMenu->addItem(
      quitItemName, quitCb, NS::String::string("q", UTF8StringEncoding));
  pAppQuitItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);
  pAppMenuItem->setSubmenu(pAppMenu);

  NS::MenuItem *pWindowMenuItem = NS::MenuItem::alloc()->init();
  NS::Menu *pWindowMenu =
      NS::Menu::alloc()->init(NS::String::string("Window", UTF8StringEncoding));

  SEL closeWindowCb = NS::MenuItem::registerActionCallback(
      "windowClose", [](void *, SEL, const NS::Object *) {
        auto pApp = NS::Application::sharedApplication();
        pApp->windows()->object<NS::Window>(0)->close();
      });
  NS::MenuItem *pCloseWindowItem = pWindowMenu->addItem(
      NS::String::string("Close Window", UTF8StringEncoding), closeWindowCb,
      NS::String::string("w", UTF8StringEncoding));
  pCloseWindowItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

  pWindowMenuItem->setSubmenu(pWindowMenu);

  pMainMenu->addItem(pAppMenuItem);
  pMainMenu->addItem(pWindowMenuItem);

  pAppMenuItem->release();
  pWindowMenuItem->release();
  pAppMenu->release();
  pWindowMenu->release();

  return pMainMenu->autorelease();
}

void AppDelegate::applicationWillFinishLaunching(
    NS::Notification *pNotification) {
  std::cout << "[AppDelegate::applicationWillFinishLaunching] set launch"
            << std::endl;
  NS::Menu *pMenu = createMenuBar();
  NS::Application *pApp =
      reinterpret_cast<NS::Application *>(pNotification->object());
  pApp->setMainMenu(pMenu);
  pApp->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void AppDelegate::applicationDidFinishLaunching(
    NS::Notification *pNotification) {
  std::cout << "[AppDelegate::applicationDidFinishLaunching] launch finish"
            << std::endl;
  CGRect frame = (CGRect){{0.0, 0.0}, {1512.0, 920.0}};

  pWindow = NS::TransferPtr(NS::Window::alloc()->init(
      frame, NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
      NS::BackingStoreBuffered, false));

  auto pDevice = MTL::CreateSystemDefaultDevice();

  pView = NS::TransferPtr(MTK::View::alloc()->init(frame, pDevice));
  pView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
  pView->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 0.0, 1.0));
  pView->setEnableSetNeedsDisplay(false);
  pView->setPaused(true);

  pRenderer = std::make_unique<engine::Renderer>(pDevice, pView->retain());
  pView->setDelegate(pRenderer.get());

  pWindow->setContentView(pView.get());
  pWindow->setTitle(
      NS::String::string("metal_dlss", NS::StringEncoding::UTF8StringEncoding));

  pWindow->makeKeyAndOrderFront(nullptr);

  NS::Application *pApp =
      reinterpret_cast<NS::Application *>(pNotification->object());
  pApp->activateIgnoringOtherApps(true);
  wait.set_value();
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(
    NS::Application *pSender) {
  std::cout << "[AppDelegate::applicationShouldTerminateAfterLastWindowClosed] "
               "closing"
            << std::endl;
  return true;
}

void AppDelegate::giveCube() {
  std::cout << "[AppDelegate::giveCube] give cube" << std::endl;
  pRenderer->giveCube();
}

void AppDelegate::draw() { pView->draw(); }
