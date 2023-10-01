#include "FPS.hpp"
#include <iostream>
using namespace x3d::engine;

FPS::FPS(long frames)
    : startTime(0), endTime(0), frames(frames), frameCount(0) {}

void FPS::update(long long now) {
  if (frameCount == 0) {
    startTime = now;
  } 
  endTime = now;
  frameCount = (frameCount + 1) % frames;
}

double FPS::getFPS() { 
  return  ((double)frames / (double)(endTime - startTime)) * 1000.0;
}
