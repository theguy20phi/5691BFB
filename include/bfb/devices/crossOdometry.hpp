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

template <int numberOfIMUs, std::uint32_t priority = TASK_PRIORITY_DEFAULT>
class CrossOdometry : public Task<priority> {
  public:
  CrossOdometry(const Odometer &iForwardOdometer,
                const Odometer &iSideOdometer,
                const IMU<numberOfIMUs> &iImus)
    : forwardOdometer(iForwardOdometer), sideOdometer(iSideOdometer), imus(iImus) {
  }

  void step() override {
    const double tempH{imus.getHeading()};
    const double deltaH{tempH - previousH};
    double localX{0.0};
    double localY{0.0};
    if (deltaH) {
      double twoSinHalfDeltaH{2.0 * sin(deltaH / 2.0)};
      localX = twoSinHalfDeltaH * sideOdometer.getDelta() / deltaH + sideOdometer.getDisp();
      localY = twoSinHalfDeltaH * forwardOdometer.getDelta() / deltaH + forwardOdometer.getDisp();
    } else {
      localX = sideOdometer.getDelta();
      localY = forwardOdometer.getDelta();
    }
    const double avgH{previousH + deltaH / 2.0};
    x += okapi::inch * (localX * cos(avgH) - localY * sin(avgH));
    y += okapi::inch * (localX * sin(avgH) + localY * cos(avgH));
    h = okapi::degree * tempH;
    previousH = tempH;
  }

  okapi::QLength X() const {
    return x;
  }

  okapi::QLength Y() const {
    return y;
  }

  okapi::QAngle H() const {
    return h;
  }

  void setX(const okapi::QLength iX) {
    x = iX;
  }

  void setY(const okapi::QLength iY) {
    y = iY;
  }

  void setH(const okapi::QAngle iH) {
    h = iH;
  }

  private:
  okapi::QLength x;
  okapi::QLength y;
  okapi::QAngle h;
  Odometer forwardOdometer;
  Odometer sideOdometer;
  IMU<numberOfIMUs> imus;
  double previousH{0};
};

#ifdef TESTING
DECLARE_TEST(initializeCrossOdometryTest);
#endif
} // namespace bfb
