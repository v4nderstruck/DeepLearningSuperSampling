#include "Scene.hpp"
#include <simd/matrix.h>
#include <simd/matrix_types.h>
#include <simd/simd.h>

using namespace x3d::world;

Scene::Scene() : root("root"), perspectiveCamera(), clearColor(0.0, 0.0, 0.0, 1.0) {
  root.setTranslation(simd::make_float3(0.0f, 0.0f, 0.0f),
                      simd::make_float3(1.0f, 1.0f, 1.0f),
                      simd::quatf(0.0, simd::make_float3(1.0, 0.0, 0.0)));

  perspectiveCamera.setInternals(simd::make_float3(0.0f, 0.0f, 7.0f), 
                                 simd::make_float3(0.0f, 0.0f, 0.0f), 
                                 simd::make_float3(0.0f, 1.0f, 0.0f),
                                 90.0f ,1512.0f/920.0f, 0.01f, 100.0f);
  perspectiveCamera.buildCamera();
}

void Scene::renderScene(MTL::RenderCommandEncoder* encoder) {
  simd::float4x4 identity = matrix_identity_float4x4;
  root.render(encoder, identity);
}

