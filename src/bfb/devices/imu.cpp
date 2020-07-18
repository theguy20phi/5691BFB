#include "imu.hpp"

namespace bfb {
IMU::IMU(const std::vector<std::uint8_t> &ports) {
  for (std::uint8_t i : ports)
    imu.push_back(pros::Imu(i));
}

void IMU::calibrate() {
  for (pros::Imu i : imu)
    std::int32_t tempValue{i.reset()};
}

double IMU::getHeading() {
  auto sumYaw = [](const pros::Imu &i1, const pros::Imu &i2) {
    return i1.get_yaw() + i2.get_yaw();
  };
  double sum{std::accumulate(imu.begin(), imu.end(), 0.0, sumYaw)};
  return headingFilter.filter(sum / imu.size());
}

bool IMU::isCalibrating() {
}
} // namespace bfb