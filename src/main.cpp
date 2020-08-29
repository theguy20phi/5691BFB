#include "main.h"

std::unique_ptr<RollersMachine> rollers;
std::unique_ptr<ChassisMachine> chassis;

void initialize() {
  rollers = std::make_unique<RollersMachine>(States::Rollers::Standby{});
  chassis = std::make_unique<ChassisMachine>(States::Chassis::Standby{});
  rollers->start();
  chassis->start();
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
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
