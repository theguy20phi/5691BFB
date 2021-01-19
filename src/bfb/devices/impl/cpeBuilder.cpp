#include "cpeBuilder.hpp"

namespace bfb {
CPEBuilder::CPEBuilder() {
}

PoseEstimatorPtr CPEBuilder::build() const {
  return PoseEstimatorPtr{
    new ComplementaryPoseEstimator{weightedPoseEstimators, weightedLandmarkers, priority}};
}

CPEBuilder CPEBuilder::withEstimator(PoseEstimatorPtr poseEstimatorPtr, double weight) {
  weightedPoseEstimators.push_back({poseEstimatorPtr, weight});
  return *this;
}

CPEBuilder CPEBuilder::withLandmarker(LandmarkerPtr landmarkerPtr, double weight) {
  weightedLandmarkers.push_back({landmarkerPtr, weight});
  return *this;
}
} // namespace bfb