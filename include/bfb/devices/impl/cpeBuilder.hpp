/**
 * @file cpeBuilder.hpp
 * @author Braden Pierce (bradenwepierce@gmail.com)
 * @brief
 * @date 2021-01-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "bfb/devices/complementaryPoseEstimator.hpp"

namespace bfb {
class CPEBuilder {
  public:
  CPEBuilder();
  PoseEstimatorPtr build() const;
  CPEBuilder withEstimator(PoseEstimatorPtr poseEstimatorPtr, double weight);
  CPEBuilder withLandmarker(LandmarkerPtr landmarkerPtr);
  CPEBuilder withPriority(int iPriority);

  private:
  WeightedPoseEstimators weightedPoseEstimators;
  LandmarkerPtr landmarker;
  int priority = TASK_PRIORITY_MAX;
};
} // namespace bfb