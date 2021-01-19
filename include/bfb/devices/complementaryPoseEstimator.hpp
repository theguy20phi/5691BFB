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
struct WeightedPoseEstimator {
  PoseEstimatorPtr estimator;
  double weight;
};

struct WeightedLandmarker {
  LandmarkerPtr landmarker;
  double weight;
};

using WeightedPoseEstimators = std::vector<WeightedPoseEstimator>;
using WeightedLandmarkers = std::vector<WeightedLandmarker>;

class ComplementaryPoseEstimator : public PoseEstimator, public Task {
  public:
  ComplementaryPoseEstimator(const WeightedPoseEstimators &iWeightedPoseEstimators,
                             const WeightedLandmarkers &iWeightedLandmarkers,
                             int iPriority = TASK_PRIORITY_MAX);
  void step();
  Pose getPose();
  void setPose(const Pose &iPose);
  void reset();
  void updatePose();

  private:
  Pose pose{0.0_in, 0.0_in, 0.0_rad};
  WeightedPoseEstimators weightedPoseEstimators;
  WeightedLandmarkers weightedLandmarkers;
};
} // namespace bfb