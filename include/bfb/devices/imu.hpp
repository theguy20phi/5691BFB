#pragma once

#include "okapi\api\filter\emaFilter.hpp"
#include "pros/imu.hpp"
#include <algorithm>
#include <functional>
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
class IMU {
  public:
  /**
   * @brief Construct a new IMU object.
   * 
   * @param ports 
   */
  IMU(const std::vector<std::uint8_t> &ports);

  /**
   * @brief Calibrate the IMUs.
   * 
   */
  void calibrate();

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
  bool isCalibrating();

  private:
  std::vector<pros::Imu> imu;
  okapi::EmaFilter headingFilter{0.5};
};
} // namespace bfb