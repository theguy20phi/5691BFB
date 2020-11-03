#include "routines.hpp"

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

Routine redLeft{[]() {
                  chassis->setState(States::Chassis::MoveTo{0.0_tile, 1.0_tile, 0.0_deg});
                  bfb::waitUntil(chassisStandby);
                },
                {bfb::Color::Red, "Red Left", "Fill left", "(x, y, h)"}};

Routine redMidLeft{[]() {}, {bfb::Color::Red, "Red Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine redMidRight{[]() {}, {bfb::Color::Red, "Red Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine redRight{[]() {}, {bfb::Color::Red, "Red Right", "Fill right", "(x, y, h)"}};

Routine redRow{[]() {}, {bfb::Color::Red, "Red Row", "Fill row", "(x, y, h)"}};

Routine skills{[]() {}, {bfb::Color::Red, "Skills", "Prog skills", "(x, y, h)"}};

Routine blueLeft{[]() {}, {bfb::Color::Blue, "Blue Left", "Fill left", "(x, y, h)"}};

Routine blueMidLeft{[]() {}, {bfb::Color::Blue, "Blue Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine blueMidRight{[]() {}, {bfb::Color::Blue, "Blue Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine blueRight{[]() {}, {bfb::Color::Blue, "Blue Right", "Fill right", "(x, y, h)"}};

Routine blueRow{[]() {}, {bfb::Color::Blue, "Blue Row", "Fill row", "(x, y, h)"}};

Routine none{[]() {}, {bfb::Color::Blue, "None", "Does nothing", "N/A"}};