#include "complementaryPoseEstimator.hpp"

namespace bfb {
ComplementaryPoseEstimator::ComplementaryPoseEstimator(
  const WeightedPoseEstimators &iWeightedPoseEstimators,
  const LandmarkerPtr &iLandmarker,
  int iPriority)
  : weightedPoseEstimators(iWeightedPoseEstimators), landmarker(iLandmarker), Task(iPriority) {
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
  Pose tempPose{0.0_in, 0.0_in, 0.0_rad};
  for (WeightedPoseEstimator estimator : weightedPoseEstimators) {
    estimator.estimator->updatePose();
    tempPose += estimator.estimator->getPose() * estimator.weight;
  }
  landmarker->updatePose(tempPose);
  if (landmarker->isReading())
    tempPose = landmarker->getPose();
  setPose(tempPose);
}

void ComplementaryPoseEstimator::setPose(const Pose &iPose) {
  for (WeightedPoseEstimator estimator : weightedPoseEstimators)
    estimator.estimator->setPose(iPose);
  landmarker->setPose(pose);
  pose = iPose;
}

void ComplementaryPoseEstimator::reset() {
  for (WeightedPoseEstimator estimator : weightedPoseEstimators)
    estimator.estimator->reset();
  landmarker->reset();
}
} // namespace bfb