#pragma once

#include "main.h"

namespace States {
namespace Chassis {
struct Standby {};
struct Control {
  int forward;
  int strafe;
  int turn;
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
  void toggleHold();
  bfb::CrossOdometry getOdometry() const;

  private:
  void controlDrive(double forward, double strafe, double turn);
  double getDistanceTo(const okapi::QAngle &h, const States::Chassis::MoveTo &moveTo);

  private:
  bfb::CrossOdometry odometry{bfb::Odometer{pros::ADIEncoder{1, 2}, 1.0},
                              bfb::Odometer{pros::ADIEncoder{3, 4}, 1.0},
                              bfb::IMU{{11, 12}}};
  pros::Motor lFWheel{1};
  pros::Motor lBWheel{2};
  pros::Motor rFWheel{3, true};
  pros::Motor rBWheel{6, true};
  bfb::Pidf xPidf{{0.0, 0.0, 0.0, 0.0}, bfb::createSettledUtil()};
  bfb::Pidf yPidf{{0.0, 0.0, 0.0, 0.0}, bfb::createSettledUtil()};
  bfb::Pidf hPidf{{0.0, 0.0, 0.0, 0.0}, bfb::createSettledUtil()};
};