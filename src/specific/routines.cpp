#include "routines.hpp"

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

Routine redLeft{[]() {
                  chassis->setState(States::Chassis::MoveTo{0.0_tile, 1.0_tile, 0.0_deg});
                  bfb::waitUntil(chassisStandby);
                },
                {Color::Red, "Red Left", "Fill left", "(x, y, h)"}};

Routine redMidLeft{[]() {}, {Color::Red, "Red Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine redMidRight{[]() {}, {Color::Red, "Red Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine redRight{[]() {}, {Color::Red, "Red Right", "Fill right", "(x, y, h)"}};

Routine redRow{[]() {}, {Color::Red, "Red Row", "Fill row", "(x, y, h)"}};

Routine skills{[]() {}, {Color::Red, "Skills", "Prog skills", "(x, y, h)"}};

Routine blueLeft{[]() {}, {Color::Blue, "Blue Left", "Fill left", "(x, y, h)"}};

Routine blueMidLeft{[]() {}, {Color::Blue, "Blue Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine blueMidRight{[]() {}, {Color::Blue, "Blue Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine blueRight{[]() {}, {Color::Blue, "Blue Right", "Fill right", "(x, y, h)"}};

Routine blueRow{[]() {}, {Color::Blue, "Blue Row", "Fill row", "(x, y, h)"}};

Routine none{[]() {}, {Color::Blue, "None", "Does nothing", "N/A"}};