/**
 * @file motionPlanner.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/utility/mathUtil.hpp"
#include <cmath>
#include <iostream>

namespace bfb {
/**
 * The motion profile class allows a mechanism to constrain its movements to what is physically
 * possible on the fly.
 */
class MotionPlanner {
  public:
  /**
   * Simple structure for motion information.
   *
   */
  struct MotionInfo {
    double P{0.0};
    double V{0.0};
    double A{0.0};
  };

  /**
   * Creates a new motion profile object.
   *
   * @param iConstraints
   * @param iDt
   */
  MotionPlanner(const MotionInfo &iConstraints, double iDt = 0.01);

  /**
   * Sets the target.
   *
   * @param iTarget
   */
  void setTarget(double iTarget);

  /**
   * Gets the next MotionInfo given current MotionInfo. Can then be fed into a controller.
   *
   * @param current
   * @return MotionInfo
   */
  MotionInfo generateNext(const MotionInfo &current);

  /**
   * Gets the current desired motion info.
   *
   * @return MotionInfo
   */
  MotionInfo getStep();

  /**
   * Gets what acceleration should be this step.
   *
   * @param current
   * @return double
   */
  double calculateA(const MotionInfo &current);

  private:
  double target{0.0};
  const MotionInfo constraints;
  MotionInfo step;
  const double dt;
};
} // namespace bfb