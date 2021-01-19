/**
 * @file crossOdometryBuilder.hpp
 * @author Braden Pierce (bradenwepierce@gmail.com)
 * @brief Implements a builder for the crossOdometry class
 * @date 2021-01-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "bfb/devices/crossOdometry.hpp"

namespace bfb {
class CrossOdometryBuilder {
  public:
  CrossOdometryBuilder();
  PoseEstimatorPtr build() const;
  CrossOdometryBuilder withForwardOdometer(const pros::ADIEncoder &encoder,
                                           double displacement,
                                           double circum = 8.639379);
  CrossOdometryBuilder
  withSideOdometer(const pros::ADIEncoder &encoder, double displacement, double circum = 8.639379);
  CrossOdometryBuilder withIMUs(const std::vector<uint8_t> &ports);

  private:
  std::shared_ptr<Odometer> forwardOdometer;
  std::shared_ptr<Odometer> sideOdometer;
  std::shared_ptr<IMU> imus;
};
} // namespace bfb