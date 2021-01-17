#pragma once

#include "bfb/flow/task.hpp"
#include "landmarker.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "poseEstimator.hpp"
#include <memory>
#include <vector>


using namespace okapi::literals;

namespace bfb {
// TODO: See if this can be made unique.
struct PoseSensor {
  std::shared_ptr<PoseEstimator> sensor;
  double weight;
};
using PoseSensors = std::vector<PoseSensor>;
class ComplementaryPoseEstimator : public PoseEstimator, public Task {
  public:
  ComplementaryPoseEstimator(const PoseSensors &iPoseSensors, const Landmarker &iLandmarker, int iPriority = TASK_PRIORITY_MAX);
  void step();
  Pose getPose();
  void setPose(const Pose &iPose);
  void reset();
  void updatePose();

  private:
  Pose pose{0.0_in, 0.0_in, 0.0_rad};
  PoseSensors poseSensors;
  Landmarker landmarker;
};
} // namespace bfb