#include "Scene.hpp"
#include <simd/matrix_types.h>
#include <simd/simd.h>

using namespace x3d::world;

Scene::Scene() : root("root"), perspectiveCamera(), clearColor(0.0, 0.0, 0.0, 1.0) {
  root.setTranslation(simd::make_float3(0.0f, 0.0f, 0.0f),
                      simd::make_float3(1.0f, 1.0f, 1.0f),
                      simd::quatf(0.0, simd::make_float3(1.0, 0.0, 0.0)));
  perspectiveCamera.setInternals(simd::make_float3(0.0f, 0.0f, 5.0f), 
                                 simd::make_float3(0.0f, 0.0f, -1.0f), 
                                 simd::make_float3(0.0f, 1.0f, 0.0f),
                                 90.0, 1.0, 0.0001, 1000.0);
  perspectiveCamera.buildCamera();
}

void Scene::renderScene(MTL::RenderCommandEncoder* encoder) {
  simd::float4x4 identity = simd::float4x4();
  identity.columns[0] = simd::make_float4(1, 0, 0, 0);
  identity.columns[1] = simd::make_float4(0, 1, 0, 0);
  identity.columns[2] = simd::make_float4(0, 0, 1, 0);
  identity.columns[3] = simd::make_float4(0, 0, 0, 1);
  root.render(encoder, identity);
}

