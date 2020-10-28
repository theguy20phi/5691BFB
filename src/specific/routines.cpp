#include "routines.hpp"

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

Routine redLeft{
  []() {
    chassis->setState(States::Chassis::MoveTo{1 * bfb::tile, 1 * bfb::tile, 0 * okapi::degree});
    bfb::waitUntil(chassisStandby);
  },
  {Color::Red, "Red Left", "Fill left", "(x, y, h)"}};

Routine redMidLeft{[]() {
                     chassis->setState(States::Chassis::MoveTo{
                       -1 * bfb::tile, -1 * bfb::tile, -180 * okapi::degree});
                   },
                   {Color::Red, "Red Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine redMidRight{
  []() {
    chassis->setState(States::Chassis::MoveTo{0 * bfb::tile, 0 * bfb::tile, 180 * okapi::degree});
  },
  {Color::Red, "Red Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine redRight{[]() {

                 },
                 {Color::Red, "Red Right", "Fill right", "(x, y, h)"}};

Routine redRow{[]() {

               },
               {Color::Red, "Red Row", "Fill row", "(x, y, h)"}};

Routine skills{[]() {

               },
               {Color::Red, "Skills", "Prog skills", "(x, y, h)"}};

Routine blueLeft{[]() {

                 },
                 {Color::Blue, "Blue Left", "Fill left", "(x, y, h)"}};

Routine blueMidLeft{[]() {

                    },
                    {Color::Blue, "Blue Mid-Left", "Fill left&mid", "(x, y, h)"}};

Routine blueMidRight{[]() {

                     },
                     {Color::Blue, "Blue Mid-Right", "Fill right&mid", "(x, y, h)"}};

Routine blueRight{[]() {

                  },
                  {Color::Blue, "Blue Right", "Fill right", "(x, y, h)"}};

Routine blueRow{[]() {

                },
                {Color::Blue, "Blue Row", "Fill row", "(x, y, h)"}};

Routine none{[]() {

             },
             {Color::Blue, "None", "Does nothing", "N/A"}};