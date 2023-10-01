#pragma once
#include <vector>
namespace x3d {
namespace engine {
class FPS {
public:
  FPS(long frames);
  // updates in ms
  void update(long long now);
  // call every `frame` frames
  double getFPS();
private:
  long long startTime;
  long long endTime;
  const long frames;
  long frameCount;
};
} // namespace engine
} // namespace x3d
