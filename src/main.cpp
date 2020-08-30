#include "main.h"

std::unique_ptr<RollersMachine> rollers;
std::unique_ptr<ChassisMachine> chassis;

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

void initialize() {
  rollers = std::make_unique<RollersMachine>(States::Rollers::Standby{});
  chassis = std::make_unique<ChassisMachine>(States::Chassis::Standby{});
  rollers->start();
  chassis->start();
}

void disabled() {
  rollers->setState(States::Rollers::Standby{});
  chassis->setState(States::Chassis::Standby{});
}

void competition_initialize() {
}

void autonomous() {
  chassis->setState(States::Chassis::MoveTo{1 * bfb::tile, 1 * bfb::tile, 180_deg});
  bfb::waitUntil(chassisStandby);
}

void opcontrol() {
  bfb::runTests();
  okapi::Controller master_remote;
  for (;;) {
    chassis->setState(
      States::Chassis::Control{master_remote.getAnalog(okapi::ControllerAnalog::leftY),
                               master_remote.getAnalog(okapi::ControllerAnalog::leftX),
                               master_remote.getAnalog(okapi::ControllerAnalog::rightX)});
    bfb::wait(10);
  }
}
