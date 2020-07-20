/**
 * @file IMU.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include "okapi/api/filter/medianFilter.hpp"
#include "pros/imu.h"
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>

namespace bfb {
/**
 * @brief Wrapper class for out-the-box pros Imu class to simplify the interface to essentially a
 * yaw gyroscope (I'm not concerned with acceleration nor other axii), change "heading" to a more
 * common axis (Z/Yaw) + remove wrap, add in a filter behind the scenes, and combine information
 * from multiple IMUs.
 *
 */
class IMU final {
  public:
  /**
   * @brief Construct a new IMU object.
   *
   * @param iPorts
   */
  IMU(const std::vector<uint8_t> &iPorts);

  /**
   * @brief Calibrate the IMUs.
   *
   */
  std::vector<int32_t> calibrate() const;

  /**
   * @brief Get the filter heading (yaw) of the IMU.
   *
   * @return double
   */
  double getHeading();

  /**
   * @brief Get the pitch.
   *
   * @return double
   */
  double getPitch() const;

  /**
   * @brief Get the roll.
   *
   * @return double
   */
  double getRoll() const;

  /**
   * @brief Get the yaw.
   *
   * @return double
   */
  double getYaw() const;

  /**
   * @brief Get the angular velocity.
   *
   * @return pros::c::imu_gyro_s_t
   */
  pros::c::imu_gyro_s_t getAngularVelocity() const;

  /**
   * @brief Get the acceleration.
   *
   * @return pros::c::imu_accel_s_t
   */
  pros::c::imu_accel_s_t getAcceleration() const;

  /**
   * @brief Get the status.
   *
   * @return std::vector<pros::c::imu_status_e_t>
   */
  std::vector<pros::c::imu_status_e_t> getStatus() const;

  /**
   * @brief Determines if the IMUs are still calibrating.
   *
   * @return bool
   */
  bool isCalibrating() const;

  private:
  std::vector<uint8_t> ports;
  okapi::MedianFilter<5> headingFilter;
};
} // namespace bfb