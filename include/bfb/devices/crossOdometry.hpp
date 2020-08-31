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
#include "okapi/api/units/QLength.hpp"
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
   * @brief Gets x.
   *
   * @return okapi::QLength
   */
  okapi::QLength X() const;

  /**
   * @brief Gets y.
   *
   * @return okapi::QLength
   */
  okapi::QLength Y() const;

  /**
   * @brief Gets h.
   *
   * @return okapi::QAngle
   */
  okapi::QAngle H() const;

  /**
   * @brief Sets x.
   *
   * @param iX
   */
  void setX(const okapi::QLength iX);

  /**
   * @brief Sets y.
   *
   * @param iY
   */
  void setY(const okapi::QLength iY);

  /**
   * @brief Sets h.
   *
   * @param iH
   */
  void setH(const okapi::QAngle iH);

  private:
  okapi::QLength x{0_in};
  okapi::QLength y{0_in};
  okapi::QAngle h{0_deg};
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
