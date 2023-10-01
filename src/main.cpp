#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "x3d/Delegate.hpp"
#include <chrono>
#include <iostream>
#include <thread>

#define FPS 200

void render_loop(x3d::AppDelegate *d) {
  while (1) {
    d->draw();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
  }
}

int main() {
  std::cout << "[main] Create ReleasePool" << std::endl;
  NS::AutoreleasePool *autoreleasePool = NS::AutoreleasePool::alloc()->init();
  std::cout << "[main] Create Window Delegate" << std::endl;
  x3d::AppDelegate Delegate;

  std::cout << "[main] Create Application" << std::endl;
  NS::Application *app = NS::Application::sharedApplication();
  std::cout << "[main] Set Window Delegate" << std::endl;
  app->setDelegate(&Delegate);
  std::cout << "[main] Run Application" << std::endl;
  std::thread render_thread(render_loop, &Delegate);
  app->run();

  render_thread.join();
  std::cout << "[main] Release Memory" << std::endl;
  autoreleasePool->release();
  return 0;
}
