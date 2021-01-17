#include "complementaryPoseEstimator.hpp"

namespace bfb {
ComplementaryPoseEstimator::ComplementaryPoseEstimator(const PoseSensors &iPoseSensors,
                                                       const Landmarker &iLandmarker,
                                                       int iPriority)
  : poseSensors(iPoseSensors), landmarker(iLandmarker), Task(iPriority) {
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
  for (PoseSensor sensor : poseSensors) {
    sensor.sensor->updatePose();
    avgPose = avgPose + sensor.sensor->getPose() * sensor.weight;
  }
  pose = avgPose;
}

void ComplementaryPoseEstimator::setPose(const Pose &iPose) {
  for (PoseSensor sensor : poseSensors)
    sensor.sensor->setPose(iPose);
  pose = iPose;
}

void ComplementaryPoseEstimator::reset() {
  for(PoseSensor sensor : poseSensors)
    sensor.sensor->reset();
}
} // namespace bfb