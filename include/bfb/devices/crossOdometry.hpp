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
class Odometer {
  public:
  Odometer(const pros::ADIEncoder &iEncoder, double iDisplacement, double iWheelCircum = 8.639379);
  double getDelta();
  double getDisp() const;

  private:
  pros::ADIEncoder encoder;
  double displacement;
  double wheelCircumference;
  int previousValue{0};
};

class CrossOdometry : public Task {
  public:
  CrossOdometry(const Odometer &iForwardOdometer,
                const Odometer &iSideOdometer,
                const IMU &iImus,
                int iPriority = TASK_PRIORITY_DEFAULT);

  void step() override;

  okapi::QLength X() const;

  okapi::QLength Y() const;

  okapi::QAngle H() const;

  void setX(const okapi::QLength iX);

  void setY(const okapi::QLength iY);

  void setH(const okapi::QAngle iH);

  private:
  okapi::QLength x;
  okapi::QLength y;
  okapi::QAngle h;
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
