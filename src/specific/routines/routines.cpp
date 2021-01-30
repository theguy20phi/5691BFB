#include "routines.hpp"

void skillsCommands() {
  chassis->setPose({1.0_tile, 10.0_in, -135.0_deg});
  rollers->setState(Rollers::FastShoot{});
  bfb::wait(300);
  rollers->setState(Rollers::Eject{});
  chassis->setState(Chassis::MoveTo{1.125_tile, 1.125_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{0.5_tile, 0.5_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  bfb::wait(2000);
  chassis->setState(Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
  bfb::waitUntil(chassisStandby, 500);
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  bfb::wait(1000);
  chassis->setState(Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
  bfb::waitUntil(chassisStandby, 500);
  chassis->setState(Chassis::MoveTo{4.375_tile, 1.625_tile, 135.0_deg});
  bfb::waitUntil(chassisStandby, 1500);
  chassis->setState(Chassis::MoveTo{5.5_tile, 0.5_tile, 135.0_deg});
  bfb::waitUntil(chassisStandby, 3000);
  bfb::wait(1000);
  chassis->setState(Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{4.5_tile, 3.0_tile, 90.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  chassis->setState(Chassis::MoveTo{5.5_tile, 3.0_tile, 90.0_deg});
  bfb::waitUntil(chassisStandby, 2000);
  bfb::wait(1000);
  for (int i = 0; i < 4; i++) {
    chassis->setState(Chassis::MoveTo{3.5_tile, 3.0_tile - 4.0_in, -90.0_deg});
    bfb::waitUntil(chassisStandby, 3000);
    chassis->setState(Chassis::MoveTo{4.25_tile, 3.0_tile - 4.0_in, -90.0_deg});
    bfb::waitUntil(chassisStandby, 3000);
  }
  chassis->setState(Chassis::MoveTo{4.75_tile, 4.75_tile, 45.0_deg});
  bfb::waitUntil(chassisStandby, 4000);
  chassis->setState(Chassis::MoveTo{5.5_tile, 6.0_tile, 45.0_deg});
}

void noneCommands() {
  chassis->setPose({1.0_tile, 10.0_in, 45.0_deg});
  rollers->setState(Rollers::FastShoot{});
}

Routine redLeft{redLeftCommands, {bfb::Color::Red, "Red Left", "Fill left", "(x, y, h)"}};
Routine redMidLeft{redMidLeftCommands,
                   {bfb::Color::Red, "Red Mid-Left", "Fill left&mid", "(x, y, h)"}};
Routine redMidRight{redMidRightCommands,
                    {bfb::Color::Red, "Red Mid-Right", "Fill right&mid", "(x, y, h)"}};
Routine redRight{redRightCommands, {bfb::Color::Red, "Red Right", "Fill right", "(x, y, h)"}};
Routine redRow{redRowCommands, {bfb::Color::Red, "Red Row", "Fill row", "(x, y, h)"}};
Routine skills{skillsCommands, {bfb::Color::Red, "Skills", "Prog skills", "(x, y, h)"}};
Routine blueLeft{blueLeftCommands, {bfb::Color::Blue, "Blue Left", "Fill left", "(x, y, h)"}};
Routine blueMidLeft{blueMidLeftCommands,
                    {bfb::Color::Blue, "Blue Mid-Left", "Fill left&mid", "(x, y, h)"}};
Routine blueMidRight{blueMidRightCommands,
                     {bfb::Color::Blue, "Blue Mid-Right", "Fill right&mid", "(x, y, h)"}};
Routine blueRight{blueRightCommands, {bfb::Color::Blue, "Blue Right", "Fill right", "(x, y, h)"}};
Routine blueRow{blueRowCommands, {bfb::Color::Blue, "Blue Row", "Fill row", "(x, y, h)"}};
Routine none{noneCommands, {bfb::Color::Blue, "None", "Does nothing", "N/A"}};