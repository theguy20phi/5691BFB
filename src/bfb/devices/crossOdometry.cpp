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
                             const IMU &iImus)
  : forwardOdometer(iForwardOdometer), sideOdometer(iSideOdometer), imus(iImus) {
  imus.calibrate();
  bfb::wait(500);
  bfb::waitUntil([=]() { return !imus.isCalibrating(); }, 6000);
}

void CrossOdometry::updatePose() {
  const double tempH{toRadians(imus.getHeading())};
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
  const double direction{atan2(localY, localX) - (previousH + deltaH / 2.0)};
  double deltaX{cos(direction) * magnitude};
  double deltaY{sin(direction) * magnitude};
  pose.x += deltaX * okapi::inch;
  pose.y += deltaY * okapi::inch;
  pose.h = tempH * okapi::radian;
  previousH = tempH;
}

Pose CrossOdometry::getPose() {
  return pose;
}

void CrossOdometry::setPose(const Pose &iPose) {
  pose = iPose;
  imus.resetHeading(iPose.h.convert(okapi::degree));
}

void CrossOdometry::reset() {
  pose = {0.0_in, 0.0_in, 0.0_rad};
  imus.resetHeading(0.0);
}
} // namespace bfb