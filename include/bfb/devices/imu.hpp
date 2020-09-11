/**
 * @file IMU.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/issue.hpp"
#include "bfb/debug/logger.hpp"
#include "okapi/api/filter/medianFilter.hpp"
#include "pros/imu.hpp"
#include <functional>
#include <numeric>

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
  IMU(const std::vector<int> &iPorts);

  /**
   * @brief Reset IMU heading to a certain value without re-calibrating.
   *
   * @param value
   */
  void resetHeading(double value = 0.0);

  /**
   * @brief Get the filter heading (yaw) of the IMU.
   *
   * @return double
   */
  double getHeading();

  /**
   * @brief Determines if the IMUs are still calibrating.
   *
   * @return bool
   */
  bool isCalibrating() const;

  /**
   * @brief Logger object for IMU.
   *
   */
  Logger<IMU> imuLog{};

  private:
  double offset{0.0};
  std::vector<pros::Imu> imus;
  okapi::MedianFilter<5> headingFilter;
};
} // namespace bfb