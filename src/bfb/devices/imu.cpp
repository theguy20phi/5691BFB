#include "imu.hpp"

namespace bfb {
IMU::IMU(const std::vector<uint8_t> &iPorts) : ports(iPorts) {
}

std::vector<int32_t> IMU::calibrate() const {
  std::vector<int32_t> temp;
  std::transform(ports.begin(), ports.end(), std::back_inserter(temp), [](const uint8_t &p) {
    return pros::c::imu_reset(p);
  });
  return temp;
}

double IMU::getHeading() {
  return headingFilter.filter(getYaw()) / ports.size();
}

double IMU::getPitch() const {
  const double sum =
    std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
      return pros::c::imu_get_euler(a).pitch + pros::c::imu_get_euler(b).pitch;
    });
  return sum / ports.size();
}

double IMU::getRoll() const {
  const double sum =
    std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
      return pros::c::imu_get_euler(a).roll + pros::c::imu_get_euler(b).roll;
    });
  return sum / ports.size();
}

double IMU::getYaw() const {
  const double sum =
    std::accumulate(ports.begin(), ports.end(), 0.0, [](const uint8_t &a, const uint8_t &b) {
      return pros::c::imu_get_euler(a).yaw + pros::c::imu_get_euler(b).yaw;
    });
  return sum / ports.size();
}

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

std::vector<pros::c::imu_status_e_t> IMU::getStatus() const {
  std::vector<pros::c::imu_status_e_t> temp;
  std::transform(ports.begin(), ports.end(), std::back_inserter(temp), [](const uint8_t &p) {
    return pros::c::imu_get_status(p);
  });
  return temp;
}

bool IMU::isCalibrating() const {
  return std::any_of(ports.begin(), ports.end(), [](const uint8_t &p) {
    return pros::c::imu_get_status(p) & pros::c::E_IMU_STATUS_CALIBRATING;
  });
}
} // namespace bfb