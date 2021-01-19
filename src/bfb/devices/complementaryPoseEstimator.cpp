#include "complementaryPoseEstimator.hpp"

namespace bfb {
ComplementaryPoseEstimator::ComplementaryPoseEstimator(
  const WeightedPoseEstimators &iWeightedPoseEstimators,
  const WeightedLandmarkers &iWeightedLandmarkers,
  int iPriority)
  : weightedPoseEstimators(iWeightedPoseEstimators),
    weightedLandmarkers(iWeightedLandmarkers),
    Task(iPriority) {
  start();
}

void ComplementaryPoseEstimator::step() {
  updatePose();
  std::cout << pose.x.convert(okapi::inch) << " " << pose.y.convert(okapi::inch) << " "
            << pose.h.convert(okapi::degree) << std::endl;
}

Pose ComplementaryPoseEstimator::getPose() {
  return pose;
}

void ComplementaryPoseEstimator::updatePose() {
  Pose avgPose{0.0_in, 0.0_in, 0.0_rad};
  for (WeightedPoseEstimator estimator : weightedPoseEstimators) {
    estimator.estimator->updatePose();
    avgPose = avgPose + estimator.estimator->getPose() * estimator.weight;
  }
  pose = avgPose;
}

void ComplementaryPoseEstimator::setPose(const Pose &iPose) {
  for (WeightedPoseEstimator estimator : weightedPoseEstimators)
    estimator.estimator->setPose(iPose);
  for (WeightedLandmarker landmarker : weightedLandmarkers)
    landmarker.landmarker->setReference(iPose);
  pose = iPose;
}

void ComplementaryPoseEstimator::reset() {
  for (WeightedPoseEstimator estimator : weightedPoseEstimators)
    estimator.estimator->reset();
}
} // namespace bfb