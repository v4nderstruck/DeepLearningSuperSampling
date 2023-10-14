#include "Debugger.hpp"
#include "Metal.hpp"
#include <iostream>

using namespace x3d::engine;

MTL::CaptureManager* Debugger::createDebugger(MTL::Device* device) {
  auto captureManager = MTL::CaptureManager::sharedCaptureManager();
  auto captureDescriptor = MTL::CaptureDescriptor::alloc()->init();

  if (captureManager->supportsDestination(MTL::CaptureDestinationGPUTraceDocument)) {
    captureDescriptor->setDestination(MTL::CaptureDestinationGPUTraceDocument);
    captureDescriptor->setOutputURL(NS::URL::alloc()->initFileURLWithPath(NS::String::string("/tmp/gpu.gputrace", NS::UTF8StringEncoding)));
  } else {
    std::cout << "[debugger] GPU Trace not supported" << std::endl;
    exit(1);
      
  }

  captureDescriptor->setCaptureObject(device);
  NS::Error *error = nullptr;
  captureManager->startCapture(captureDescriptor, &error);
  if (error) {
    std::cout << "[debugger] Error: " << error->localizedDescription()->utf8String() << std::endl;
  }
  return captureManager;
};
