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
  chassis->setPose({1.5_tile, 0.5_tile - 3.0_in, -135.0_deg});
  rollers->setState(Rollers::Detach{});
  bfb::wait(300);
  rollers->setState(Rollers::Intake{});
  chassis->setState(Chassis::MoveTo{1.125_tile, 1.125_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  chassis->setState(Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::Intake{});
  chassis->setState(Chassis::MoveTo{0.5_tile, 0.5_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  bfb::wait(50);
  rollers->setState(Rollers::Shoot{});
  bfb::waitUntil(isNotInEjector);
  bfb::wait(300);
  chassis->setState(Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
  bfb::wait(100);
  rollers->setState(Rollers::Outtake{});
  bfb::waitUntil(chassisStandby, 500);
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1000);
  rollers->setState(Rollers::Intake{});
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1000);
  chassis->setState(Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  rollers->setState(Rollers::Shoot{});
  bfb::waitUntil(isNotInEjector);
  bfb::wait(300);
  rollers->setState(Rollers::Outtake{});
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::wait(250);
  bfb::waitUntil(chassisStandby, 750);
  rollers->setState(Rollers::Intake{});
  chassis->setState(Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  chassis->setState(Chassis::MoveTo{7.0_tile, -1.0_tile, 135.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  bfb::wait(100);
  rollers->setState(Rollers::Shoot{});
}