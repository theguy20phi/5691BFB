/**
 * @file poseSensor.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"


namespace bfb {
/**
 * @brief Contains basic information about the pose of the robot (or other object).
 *
 */
struct Pose {
  okapi::QLength x;
  okapi::QLength y;
  okapi::QAngle h;
};

Pose operator + (const Pose &lhs, const Pose &rhs);
Pose operator - (const Pose &lhs, const Pose &rhs);
Pose operator * (const Pose &lhs, double factor);
Pose operator / (const Pose &lhs, double denom);
bool operator == (const Pose &lhs, const Pose &rhs);
bool operator != (const Pose &lhs, const Pose &rhs);


/**
 * @brief Class to provide a common interface for devices related to pose estimation.
 */
class PoseEstimator {
  public:
  virtual Pose getPose() = 0;
  virtual void updatePose() = 0;
  virtual void setPose(const Pose &iPose) = 0;
  virtual void reset() = 0;
};
} // namespace bfb