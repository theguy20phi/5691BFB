#include "cpeBuilder.hpp"

namespace bfb {
CPEBuilder::CPEBuilder() {
}

PoseEstimatorPtr CPEBuilder::build() const {
  return PoseEstimatorPtr{
    new ComplementaryPoseEstimator{weightedPoseEstimators, landmarker, priority}};
}

CPEBuilder CPEBuilder::withEstimator(PoseEstimatorPtr poseEstimatorPtr, double weight) {
  weightedPoseEstimators.push_back({poseEstimatorPtr, weight});
  return *this;
}

CPEBuilder CPEBuilder::withLandmarker(LandmarkerPtr landmarkerPtr) {
  landmarker = landmarkerPtr;
  return *this;
}
} // namespace bfb