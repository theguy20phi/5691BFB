/**
 * @file roller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

namespace States {
namespace Chassis {
struct Standby {};
struct Control {
  double forward;
  double strafe;
  double turn;
};
struct MoveTo {
  okapi::QLength x;
  okapi::QLength y;
  okapi::QAngle h;
};
using ChassisStates = std::variant<Standby, Control, MoveTo>;
} // namespace Chassis
} // namespace States

class ChassisMachine : public bfb::StateMachine<ChassisMachine, States::Chassis::ChassisStates> {
  public:
  ChassisMachine(const States::Chassis::ChassisStates &iState);
  void behavior(const States::Chassis::Standby &standby);
  void behavior(const States::Chassis::Control &control);
  void behavior(const States::Chassis::MoveTo &moveTo);

  private:
  bfb::CrossOdometry odometry{bfb::Odometer{pros::ADIEncoder{1, 2}, 1.0},
                              bfb::Odometer{pros::ADIEncoder{3, 4}, 1.0},
                              bfb::IMU{{9, 10}}};
};