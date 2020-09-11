#include "imu.hpp"

namespace bfb {
IMU::IMU(const std::vector<int> &iPorts) {
  imuLog.log("Imu created", {});
  for (int port : iPorts)
    imus.push_back(pros::Imu{port});
}

void IMU::resetHeading(double value) {
  imuLog.log("Imu reset to: " + std::to_string(value), {});
  offset = value - getHeading();
}

double IMU::getHeading() {
  double yawSum{0.0};
  for (pros::Imu imu : imus)
    yawSum += imu.get_yaw();
  return offset + headingFilter.filter(yawSum / imus.size());
}

bool IMU::isCalibrating() const {
  if (std::any_of(imus.begin(), imus.end(), [](const pros::Imu &imu) {
        return imu.get_status() == pros::c::E_IMU_STATUS_ERROR;
      }))
    static Issue imuInitIssue{"IMUInit", Severity::High};
  return std::any_of(imus.begin(), imus.end(), [](const pros::Imu &imu) {
    return imu.get_status() == pros::c::E_IMU_STATUS_CALIBRATING;
  });
}
} // namespace bfb