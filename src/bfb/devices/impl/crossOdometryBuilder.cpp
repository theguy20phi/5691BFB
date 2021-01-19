#include "crossOdometryBuilder.hpp"

namespace bfb {
CrossOdometryBuilder::CrossOdometryBuilder() {
}

PoseEstimatorPtr CrossOdometryBuilder::build() const {
  return PoseEstimatorPtr{new CrossOdometry{*forwardOdometer, *sideOdometer, *imus}};
}

CrossOdometryBuilder CrossOdometryBuilder::withForwardOdometer(const pros::ADIEncoder &encoder,
                                                               double displacement,
                                                               double circum) {
  forwardOdometer = std::make_shared<Odometer>(encoder, displacement, circum);
  return *this;
}

CrossOdometryBuilder CrossOdometryBuilder::withSideOdometer(const pros::ADIEncoder &encoder,
                                                            double displacement,
                                                            double circum) {
  sideOdometer = std::make_shared<Odometer>(encoder, displacement, circum);
  return *this;
}

CrossOdometryBuilder CrossOdometryBuilder::withIMUs(const std::vector<uint8_t> &ports) {
  imus = std::make_shared<IMU>(ports);
return *this;
} // namespace bfb
} // namespace bfb