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
#include "pros/imu.h"
#include <array>
#include <functional>
#include <numeric>

namespace bfb {
/**
 * @brief Wrapper class for out-the-box pros Imu class to simplify the interface to essentially a
 * yaw gyroscope (I'm not concerned with acceleration nor other axii), change "heading" to a more
 * common axis (Z/Yaw) + remove wrap, add in a filter behind the scenes, and combine information
 * from multiple IMUs.
 *
 * @tparam size
 */
template <int size> class IMU final {
  public:
  /**
   * @brief Construct a new IMU object.
   *
   * @param iPorts
   */
  IMU(const std::array<uint8_t, size> &iPorts) : ports(iPorts) {
    imuLog.log("Imu created", {});
  }

  /**
   * @brief Calibrate the IMUs. Gives issue if any IMU initializes improperly.
   *
   */
  std::array<int32_t, size> calibrate() const {
    imuLog.log("Imu calibrating...", {});
    std::array<int32_t, size> temp;
    std::transform(ports.begin(), ports.end(), std::back_inserter(temp), [](const uint8_t &p) {
      return pros::c::imu_reset(p);
    });
    if (std::any_of(temp.begin(), temp.end(), [](const int32_t &p) { return p != 1; }))
      static Issue imuInitIssue{"IMUInit", Severity::High};
    return temp;
  };

  /**
   * @brief Reset IMU heading to a certain value without re-calibrating.
   *
   * @param value
   */
  void resetHeading(double value = 0.0) {
    imuLog.log("Imu reset to: " + std::to_string(value), {});
    offset = value - getHeading();
  }

  /**
   * @brief Get the filter heading (yaw) of the IMU.
   *
   * @return double
   */
  double getHeading() {
    return offset + headingFilter.filter(getYaw()) / ports.size();
  }

  /**
   * @brief Get the pitch.
   *
   * @return double
   */
  double getPitch() const {
    const double sum =
      std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
        return pros::c::imu_get_euler(a).pitch + pros::c::imu_get_euler(b).pitch;
      });
    return sum / ports.size();
  }

  /**
   * @brief Get the roll.
   *
   * @return double
   */
  double getRoll() const {
    const double sum =
      std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
        return pros::c::imu_get_euler(a).roll + pros::c::imu_get_euler(b).roll;
      });
    return sum / ports.size();
  }

  /**
   * @brief Get the yaw.
   *
   * @return double
   */
  double getYaw() const {
    const double sum =
      std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
        return pros::c::imu_get_euler(a).yaw + pros::c::imu_get_euler(b).yaw;
      });
    return sum / ports.size();
  }

  /**
   * @brief Get the angular velocity.
   *
   * @return pros::c::imu_gyro_s_t
   */
  pros::c::imu_gyro_s_t getAngularVelocity() const {
    const pros::c::imu_gyro_s_t sum =
      std::accumulate(ports.begin(),
                      ports.end(),
                      pros::c::imu_gyro_s_t{0.0, 0.0, 0.0},
                      [](const pros::c::imu_gyro_s_t &a, const uint8_t &b) {
                        pros::c::imu_gyro_s_t bVal{pros::c::imu_get_gyro_rate(b)};
                        return pros::c::imu_gyro_s_t{a.x + bVal.x, a.y + bVal.y, a.z + bVal.z};
                      });
    return pros::c::imu_gyro_s_t{sum.x / ports.size(), sum.y / ports.size(), sum.z / ports.size()};
  }

  /**
   * @brief Get the acceleration.
   *
   * @return pros::c::imu_accel_s_t
   */
  pros::c::imu_accel_s_t getAcceleration() const {
    const pros::c::imu_accel_s_t sum =
      std::accumulate(ports.begin(),
                      ports.end(),
                      pros::c::imu_accel_s_t{0.0, 0.0, 0.0},
                      [](const pros::c::imu_accel_s_t &a, const uint8_t &b) {
                        pros::c::imu_accel_s_t bVal{pros::c::imu_get_gyro_rate(b)};
                        return pros::c::imu_accel_s_t{a.x + bVal.x, a.y + bVal.y, a.z + bVal.z};
                      });
    return pros::c::imu_accel_s_t{sum.x / ports.size(), sum.y / ports.size(), sum.z / ports.size()};
  }

  /**
   * @brief Get the status.
   *
   * @return std::array<pros::c::imu_status_e_t, size>
   */
  std::array<pros::c::imu_status_e_t, size> getStatus() const {
    std::array<pros::c::imu_status_e_t, size> temp;
    std::transform(ports.begin(), ports.end(), std::back_inserter(temp), [](const uint8_t &p) {
      return pros::c::imu_get_status(p);
    });
    return temp;
  };

  /**
   * @brief Determines if the IMUs are still calibrating.
   *
   * @return bool
   */
  bool isCalibrating() const {
    return std::any_of(ports.begin(), ports.end(), [](const uint8_t &p) {
      return pros::c::imu_get_status(p) == pros::c::E_IMU_STATUS_CALIBRATING;
    });
  }

  /**
   * @brief Logger object for IMU.
   *
   */
  Logger<IMU<size>> imuLog{};

  private:
  double offset{0.0};
  std::array<uint8_t, size> ports;
  okapi::MedianFilter<5> headingFilter;
};
} // namespace bfb