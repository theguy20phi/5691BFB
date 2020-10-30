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
#include "pros/adi.hpp"

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
   * @brief Gets the x value of the bot.
   *
   * @return double
   */
  double X() const;

  /**
   * @brief Gets the y value of the bot.
   *
   * @return double
   */
  double Y() const;

  /**
   * @brief Gets the h value of the bot.
   *
   * @return double
   */
  double H() const;

  /**
   * @brief Resets the odometry.
   *
   * @param iX
   * @param iY
   * @param iH
   */
  void reset(double iX = 0.0, double iY = 0.0, double iH = 0.0);

  private:
  double x{0.0};
  double y{0.0};
  double h{0.0};
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
