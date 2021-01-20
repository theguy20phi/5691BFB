#include "nullLandmarker.hpp"

namespace bfb {
void NullLandmarker::updatePose(const Pose &iReferencePose) {
  pose = iReferencePose;
}

void NullLandmarker::setPose(const Pose &iReferencePose) {
  pose = iReferencePose;
}

bool NullLandmarker::isReading() {
  return false;
}

Pose NullLandmarker::getPose() {
  return pose;
}

void NullLandmarker::reset() {
  pose = {0.0_tile, 0.0_tile, 0.0_deg};
}
} // namespace bfb