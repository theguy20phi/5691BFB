#include "imu.hpp"

namespace bfb {
IMU::IMU(const std::vector<uint8_t> &iPorts) {
  imuLog.log("Imu created", {});
  for (uint8_t port : iPorts)
    imus.push_back(pros::Imu{port});
}

void IMU::resetHeading(double value) {
  imuLog.log("Imu reset to: " + std::to_string(value), {});
  offset += value - getHeading();
}

double IMU::getHeading() {
  double sum{0.0};
  for (pros::Imu imu : imus)
    sum += imu.get_rotation();
  return offset + headingFilter.filter(sum / imus.size());
}

void IMU::calibrate() {
  for (pros::Imu imu : imus)
    imu.reset();
}

bool IMU::isCalibrating() const {
  for (pros::Imu imu : imus) {
    if (imu.is_calibrating())
      return true;
  }
  return false;
}
} // namespace bfb