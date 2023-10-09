#include "Scene.hpp"
#include <simd/simd.h>

using namespace x3d::world;

Scene::Scene() : root("root"), perspectiveCamera() {
  root.setTranslation(simd::make_float3(0.0f, 0.0f, 0.0f),
                      simd::make_float3(1.0f, 1.0f, 1.0f),
                      simd::quatf(0.0, simd::make_float3(1.0, 0.0, 0.0)));
  perspectiveCamera.setInternals(simd::make_float3(0.0f, 0.0f, 0.0f), 
                                 simd::make_float3(0.0f, 1.0f, 0.0f), 
                                 simd::make_float3(0.0f, 0.0f, 1.0f),
                                 90.0, 1.0, 0.0001, 1000.0);
  perspectiveCamera.buildCamera();
}

void Scene::renderScene(MTL::RenderCommandEncoder* encoder) {
  root.render(encoder);
}

