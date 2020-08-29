#include "crossOdometry.hpp"

namespace bfb {
Odometer::Odometer(const pros::ADIEncoder &iEncoder,
                   double iDisplacement,
                   double iWheelCircum)
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

DEFINE_TEST(initializeCrossOdometryTest)
CrossOdometry<2> odometry{Odometer{pros::ADIEncoder{1, 2}, 1.0}, Odometer{pros::ADIEncoder{3, 4}, 1.0}, IMU<2>{{1, 2}}};
END_TEST
} // namespace bfb