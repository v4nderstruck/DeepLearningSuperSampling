#include <simd/vector_make.h>
#include <tuple>
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "x3d/Delegate.hpp"
#include "x3d/mesh/BasicMeshes.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#define FPS 60

using namespace x3d::world;
void render_loop(x3d::AppDelegate *d) {


  auto root = &(d->pRenderer->scene.root);

  std::cout << "[render_loop] Scene ptr " << std::hex << (void *)root
            << std::endl;
  Node *actual_cube =
      Node::new_cube(root, std::string("cube"), d->pRenderer->pDevice.get(),
                     d->pRenderer->pLibrary.get(), 3.0, 3.0,3.0,
                     RGBAColor{1.0, 1.0, 0.0, 1.0});
  auto pixelFormat = d->pRenderer->getPixelFormat();
  //actual_cube->mesh->BuildVertexDescriptor();  
  actual_cube->mesh->BuildRenderPipelineState(
      d->pRenderer->pDevice.get(), d->pRenderer->pLibrary.get(),
      std::get<0>(pixelFormat), std::get<1>(pixelFormat));
  std::cout << "[render_loop] Cube ptr " << std::hex << (void *)actual_cube
            << std::endl;
  std::cout << "[render_loop] Scene children " << d->pRenderer->scene.root.children.size()
            << std::endl;
  long c = 1;
  while (1) {
    actual_cube->rotate((5.0 * c * M_PI) /180.0, simd::make_float3(1.0f, 0.0f, 0.0f));
    d->draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    c++;
  }
}

int main() {
  std::cout << "[main] Create ReleasePool" << std::endl;
  NS::AutoreleasePool *autoreleasePool = NS::AutoreleasePool::alloc()->init();
  std::cout << "[main] Create Window Delegate" << std::endl;
  x3d::AppDelegate Delegate;

  std::thread render_thread(
      [thread_wait = Delegate.wait.get_future(), &Delegate]() mutable {
        thread_wait.wait();
        render_loop(&Delegate);
      });

  std::cout << "[main] Create Application" << std::endl;
  NS::Application *app = NS::Application::sharedApplication();
  std::cout << "[main] Set Window Delegate" << std::endl;
  app->setDelegate(&Delegate);
  std::cout << "[main] Run Application" << std::endl;

  app->run();

  std::cout << "[main] Release Memory" << std::endl;
  autoreleasePool->release();
  return 0;
}
