/**
 * @file crossOdometry.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/test.hpp"
#include "bfb/devices/imu.hpp"
#include "bfb/flow/task.hpp"
#include "bfb/utility/mathUtil.hpp"
#include "poseEstimator.hpp"
#include "pros/adi.hpp"

using namespace okapi::literals;

namespace bfb {
/**
 * @brief Odometer class used to represent odometer wheels in CrossOdometry.
 *
 */
class Odometer {
  public:
  /**
   * @brief Construct a new Odometer object
   *
   * @param iEncoder
   * @param iDisplacement
   * @param iWheelCircum
   */
  Odometer(const pros::ADIEncoder &iEncoder, double iDisplacement, double iWheelCircum = 8.639379);

  /**
   * @brief Get the Delta object
   *
   * @return double
   */
  double getDelta();
  double getDisp() const;

  private:
  pros::ADIEncoder encoder;
  double displacement;
  double wheelCircumference;
  int previousValue{0};
};

/**
 * @brief The CrossOdometry class provides the implementation for a form
 * of odometry that uses two odometers that are placed perpendicular of one another and one or more
 * imus.
 *
 */
class CrossOdometry : public PoseEstimator {
  public:
  /**
   * @brief Construct a new Cross Odometry object
   *
   * @param iForwardOdometer
   * @param iSideOdometer
   * @param iImus
   * @param iPriority
   */
  CrossOdometry(const Odometer &iForwardOdometer,
                const Odometer &iSideOdometer,
                const IMU &iImus);

  void updatePose() override;

  /**
   * @brief Get the estimated pose according to odometry.
   * @return Pose
   */
  Pose getPose() override;

  /**
   * @brief Resets the odometry.
   *
   * @param iPose
   */
  void setPose(const Pose &iPose) override;

  /**
   * @brief Performs a basic reset of odometry (clearing pose + resetting sensors)
   */
  void reset() override;

  private:
  Pose pose{0.0_in, 0.0_in, 0.0_rad};
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
