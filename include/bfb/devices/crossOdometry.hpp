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
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
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
class CrossOdometry : public Task {
  public:
  /**
   * @brief Structure to represent position data.
   *
   */
  struct Pose {
    okapi::QLength X{0_in};
    okapi::QLength Y{0_in};
    okapi::QAngle H{0_deg};
    okapi::QSpeed VX{0_mps};
    okapi::QSpeed VY{0_mps};
    okapi::QAngularSpeed W{0_rpm};
  };

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
                const IMU &iImus,
                int iPriority = TASK_PRIORITY_DEFAULT);

  void step() override;

  /**
   * @brief Get the Pose object.
   *
   * @return Pose
   */
  Pose getPose() const;

  /**
   * @brief Resets the odometry.
   *
   * @param iPose
   */
  void reset(const Pose &iPose = Pose{0_in, 0_in, 0_deg, 0_mps, 0_mps, 0_rpm});

  private:
  Pose pose;
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
