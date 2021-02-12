#include "redCommands.hpp"

void redLeftCommands() {
}

void redMidLeftCommands() {
}

void redMidRightCommands() {
}

void redRightCommands() {
}

void redRowCommands() {
  chassis->setPose({2.0_tile, 10.0_in, 180.0_deg});
  rollers->setState(Rollers::Detach{});
  chassis->setState(Chassis::MoveTo{2.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::Standby{});
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  chassis->setState(Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::FastShoot{});
  bfb::wait(1000);
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::Intake{});
  chassis->setState(Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  chassis->setState(Chassis::MoveTo{0.75_tile, 0.75_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  bfb::wait(750);
  rollers->setState(Rollers::Standby{});
  chassis->setState(Chassis::MoveTo{0.0_tile, 0.0_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::FastShoot{});
}