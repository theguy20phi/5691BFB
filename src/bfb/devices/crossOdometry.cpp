#include "crossOdometry.hpp"

namespace bfb {
Odometer::Odometer(const pros::ADIEncoder &iEncoder, double iDisplacement, double iWheelCircum)
  : encoder(iEncoder), displacement(iDisplacement), wheelCircumference(iWheelCircum) {
}

double Odometer::getDelta() {
  int delta{encoder.get_value() - previousValue};
  previousValue = encoder.get_value();
  return (delta / 360.0) * wheelCircumference;
}

double Odometer::getDisp() const {
  return displacement;
}

CrossOdometry::CrossOdometry(const Odometer &iForwardOdometer,
                             const Odometer &iSideOdometer,
                             const IMU &iImus,
                             int iPriority)
  : forwardOdometer(iForwardOdometer), sideOdometer(iSideOdometer), imus(iImus), Task(iPriority) {
  imus.calibrate();
  bfb::wait(500);
  while (imus.isCalibrating())
    bfb::wait(bfb::Wait::generalDelay);
}

void CrossOdometry::step() {
  const double tempH{imus.getHeading() * M_PI / 180};
  const double deltaH{tempH - previousH};
  double localX{0.0};
  double localY{0.0};
  if (deltaH) {
    double twoSinHalfDeltaH{2.0 * sin(deltaH / 2.0)};
    localX = twoSinHalfDeltaH * (sideOdometer.getDelta() / deltaH + sideOdometer.getDisp());
    localY = twoSinHalfDeltaH * (forwardOdometer.getDelta() / deltaH + forwardOdometer.getDisp());
  } else {
    localX = sideOdometer.getDelta();
    localY = forwardOdometer.getDelta();
  }
  const double magnitude{sqrt(localX * localX + localY * localY)};
  const double direction{atan2(localY, localX) - previousH + deltaH / 2.0};
  x += okapi::inch * cos(direction) * magnitude;
  y += okapi::inch * sin(direction) * magnitude;
  h = okapi::radian * tempH;
  previousH = tempH;
}

okapi::QLength CrossOdometry::X() const {
  return x;
}

okapi::QLength CrossOdometry::Y() const {
  return y;
}

okapi::QAngle CrossOdometry::H() const {
  return h;
}

void CrossOdometry::setX(const okapi::QLength iX) {
  x = iX;
}

void CrossOdometry::setY(const okapi::QLength iY) {
  y = iY;
}

void CrossOdometry::setH(const okapi::QAngle iH) {
  imus.resetHeading(iH.convert(okapi::degree));
  h = iH;
}

void CrossOdometry::reset(const okapi::QLength iX,
                          const okapi::QLength iY,
                          const okapi::QAngle iH) {
  setX(iX);
  setY(iY);
  setH(iH);
}

DEFINE_TEST(initializeCrossOdometryTest)
CrossOdometry odometry{Odometer{pros::ADIEncoder{1, 2}, 1.0},
                       Odometer{pros::ADIEncoder{3, 4}, 1.0},
                       IMU{{1, 2}}};
END_TEST
} // namespace bfb