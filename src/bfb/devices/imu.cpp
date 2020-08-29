#include "imu.hpp"

namespace bfb {
/**
 * @brief Construct a new IMU object.
 *
 * @param iPorts
 */
IMU::IMU(const std::vector<uint8_t> &iPorts) : ports(iPorts) {
  imuLog.log("Imu created", {});
}

/**
 * @brief Calibrate the IMUs. Gives issue if any IMU initializes improperly.
 *
 */
std::vector<int32_t> IMU::calibrate() const {
  imuLog.log("Imu calibrating...", {});
  std::vector<int32_t> temp;
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
void IMU::resetHeading(double value) {
  imuLog.log("Imu reset to: " + std::to_string(value), {});
  offset = value - getHeading();
}

/**
 * @brief Get the filter heading (yaw) of the IMU.
 *
 * @return double
 */
double IMU::getHeading() {
  return offset + headingFilter.filter(getYaw()) / ports.size();
}

/**
 * @brief Get the pitch.
 *
 * @return double
 */
double IMU::getPitch() const {
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
double IMU::getRoll() const {
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
double IMU::getYaw() const {
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
pros::c::imu_gyro_s_t IMU::getAngularVelocity() const {
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
pros::c::imu_accel_s_t IMU::getAcceleration() const {
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
 * @return std::vector<pros::c::imu_status_e_t>
 */
std::vector<pros::c::imu_status_e_t> IMU::getStatus() const {
  std::vector<pros::c::imu_status_e_t> temp;
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
bool IMU::isCalibrating() const {
  return std::any_of(ports.begin(), ports.end(), [](const uint8_t &p) {
    return pros::c::imu_get_status(p) == pros::c::E_IMU_STATUS_CALIBRATING;
  });
}
} // namespace bfb