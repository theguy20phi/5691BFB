#include "routines.hpp"

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

auto isBlue = []() -> bool {
  return rollers->isInEjector() && rollers->getBallColor() == bfb::Color::Blue;
};

auto isRed = []() -> bool {
  return rollers->isInEjector() && rollers->getBallColor() == bfb::Color::Red;
};

auto isInEjector = []() -> bool { return rollers->isInEjector(); };

auto isNotInEjector = []() -> bool { return !rollers->isInEjector(); };

Routine redLeft{[]() {}, {bfb::Color::Red, "Red Left", "Fill left", "(x, y, h)"}};

Routine redMidLeft{[]() {}, {bfb::Color::Red, "Red Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine redMidRight{[]() {}, {bfb::Color::Red, "Red Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine redRight{[]() {}, {bfb::Color::Red, "Red Right", "Fill right", "(x, y, h)"}};

Routine redRow{[]() {
                 chassis->reset(1.5_tile, 0.5_tile - 3.0_in, -135.0_deg);
                 rollers->setState(States::Rollers::Intake{});
                 chassis->setState(States::Chassis::MoveTo{1.125_tile, 1.125_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 chassis->setState(States::Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 chassis->setState(States::Chassis::MoveTo{0.5_tile, 0.5_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 bfb::wait(100);
                 rollers->setState(States::Rollers::Shoot{});
                 bfb::waitUntil(isNotInEjector);
                 bfb::wait(250);
                 chassis->setState(States::Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
                 bfb::wait(100);
                 rollers->setState(States::Rollers::Hold{});
                 bfb::waitUntil(chassisStandby, 500);
                 rollers->setState(States::Rollers::Intake{});
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 1000);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 1000);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 rollers->setState(States::Rollers::Shoot{});
                 bfb::waitUntil(isNotInEjector);
                 bfb::wait(1000);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
                 bfb::wait(100);
                 rollers->setState(States::Rollers::Detach{});
                 bfb::waitUntil(chassisStandby, 500);
                 rollers->setState(States::Rollers::Intake{});
                 chassis->setState(States::Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
                 bfb::waitUntil(chassisStandby, 1500);
                 chassis->setState(States::Chassis::MoveTo{5.5_tile, 0.5_tile, 135.0_deg});
                 bfb::waitUntil(chassisStandby, 3000);
                 bfb::wait(100);
                 rollers->setState(States::Rollers::Shoot{});
                 bfb::waitUntil(isNotInEjector);
                 bfb::wait(500);
                 rollers->setState(States::Rollers::Detach{});
                 chassis->setState(States::Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
               },
               {bfb::Color::Red, "Red Row", "Fill row", "(x, y, h)"}};

Routine skills{[]() {
                 chassis->reset(1.0_tile, 10.0_in, 45.0_deg);
                 rollers->setState(States::Rollers::FastShoot{});
                 bfb::wait(300);
                 rollers->setState(States::Rollers::Intake{});
                 chassis->setState(States::Chassis::MoveTo{1.5_tile, 1.0_tile, 45.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 chassis->setState(States::Chassis::MoveTo{1.125_tile, 1.125_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 chassis->setState(States::Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 rollers->setState(States::Rollers::Standby{});
                 chassis->setState(States::Chassis::MoveTo{0.4_tile, 0.5_tile, -135.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 rollers->setState(States::Rollers::Shoot{});
                 bfb::waitUntil(isNotInEjector);
                 bfb::wait(500);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 2.0_tile, 90.0_deg});
                 rollers->setState(States::Rollers::Detach{});
                 bfb::wait(400);
                 rollers->setState(States::Rollers::Intake{});
                 bfb::waitUntil(chassisStandby, 4000);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 1000);
                 rollers->setState(States::Rollers::Standby{});
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 1000);
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
                 bfb::waitUntil(chassisStandby, 2000);
                 rollers->setState(States::Rollers::Shoot{});
                 bfb::waitUntil(isNotInEjector);
                 bfb::wait(1000);
                 rollers->setState(States::Rollers::Detach{});
                 chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
                 bfb::wait(500);
               },
               {bfb::Color::Red, "Skills", "Prog skills", "(x, y, h)"}};

Routine blueLeft{[]() {
                   chassis->reset(1.5_tile, 0.5_tile - 3.0_in, -135.0_deg);
                   rollers->setState(States::Rollers::Intake{});
                   chassis->setState(States::Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
                   bfb::waitUntil(chassisStandby, 2000);
                   chassis->setState(States::Chassis::MoveTo{0.63_tile, 0.55_tile, -135.0_deg});
                   bfb::waitUntil(chassisStandby, 4000);
                   bfb::wait(100);
                   rollers->setState(States::Rollers::Cycle{});
                   bfb::wait(1000);
                   rollers->setState(States::Rollers::FastShoot{});
                   bfb::wait(1000);
                   chassis->setState(States::Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
                   bfb::waitUntil(chassisStandby, 500);
                   chassis->setState(States::Chassis::MoveTo{1.5_tile, 1.0_tile, -180.0_deg});
                   rollers->setState(States::Rollers::Shoot{});
                   /*
                    bfb::waitUntil(chassisStandby, 2000);
                    rollers->setState(States::Rollers::Shoot{});
                    chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.25_tile, -180.0_deg});
                    bfb::waitUntil(chassisStandby, 2000);
                    rollers->setState(States::Rollers::Intake{});
                    chassis->setState(States::Chassis::MoveTo{3.0_tile, 0.8_tile, -180.0_deg});
                    */
                 },
                 {bfb::Color::Blue, "Blue Left", "Fill left", "(x, y, h)"}};

Routine blueMidLeft{[]() {}, {bfb::Color::Blue, "Blue Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine blueMidRight{[]() {}, {bfb::Color::Blue, "Blue Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine blueRight{[]() {}, {bfb::Color::Blue, "Blue Right", "Fill right", "(x, y, h)"}};

Routine blueRow{[]() {
                  chassis->reset(1.5_tile, 0.5_tile - 3.0_in, -135.0_deg);
                  rollers->setState(States::Rollers::Intake{});
                  chassis->setState(States::Chassis::MoveTo{1.125_tile, 1.125_tile, -135.0_deg});
                  bfb::waitUntil(chassisStandby, 2000);
                  chassis->setState(States::Chassis::MoveTo{1.0_tile, 1.0_tile, -135.0_deg});
                  bfb::waitUntil(chassisStandby, 2000);
                  chassis->setState(States::Chassis::MoveTo{0.5_tile, 0.5_tile, -135.0_deg});
                  bfb::waitUntil(chassisStandby, 2000);
                  bfb::wait(100);
                  rollers->setState(States::Rollers::Shoot{});
                  bfb::waitUntil(isNotInEjector);
                  bfb::wait(250);
                  chassis->setState(States::Chassis::MoveTo{1.25_tile, 1.25_tile, -135.0_deg});
                  bfb::wait(100);
                  rollers->setState(States::Rollers::Hold{});
                  bfb::waitUntil(chassisStandby, 500);
                  rollers->setState(States::Rollers::Intake{});
                  chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
                  bfb::waitUntil(chassisStandby, 1000);
                  chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.0_tile, 180.0_deg});
                  bfb::waitUntil(chassisStandby, 1000);
                  chassis->setState(States::Chassis::MoveTo{3.0_tile, 0.5_tile, 180.0_deg});
                  bfb::waitUntil(chassisStandby, 2000);
                  rollers->setState(States::Rollers::Shoot{});
                  bfb::waitUntil(isNotInEjector);
                  bfb::wait(1000);
                  chassis->setState(States::Chassis::MoveTo{3.0_tile, 1.5_tile, 180.0_deg});
                  bfb::wait(100);
                  rollers->setState(States::Rollers::Detach{});
                  bfb::waitUntil(chassisStandby, 500);
                  rollers->setState(States::Rollers::Intake{});
                  chassis->setState(States::Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
                  bfb::waitUntil(chassisStandby, 1500);
                  chassis->setState(States::Chassis::MoveTo{5.5_tile, 0.5_tile, 135.0_deg});
                  bfb::waitUntil(chassisStandby, 3000);
                  bfb::wait(100);
                  rollers->setState(States::Rollers::Shoot{});
                  bfb::waitUntil(isNotInEjector);
                  bfb::wait(500);
                  rollers->setState(States::Rollers::Detach{});
                  chassis->setState(States::Chassis::MoveTo{4.5_tile, 1.5_tile, 135.0_deg});
                },
                {bfb::Color::Blue, "Blue Row", "Fill row", "(x, y, h)"}};

Routine none{[]() {}, {bfb::Color::Blue, "None", "Does nothing", "N/A"}};