#include "controls.hpp"

void chassisControls() {
  chassis->setState(
    States::Chassis::Control{master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 100,
                             master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) * 100,
                             master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 100});
}

void rollerControls() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
      rollers->setState(States::Rollers::Cycle{match->getColor()});
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
      rollers->setState(States::Rollers::FastShoot{});
    else
      rollers->setState(States::Rollers::Shoot{});
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    rollers->setState(States::Rollers::Intake{});
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    rollers->setState(States::Rollers::Outtake{});
  else
    rollers->setState(States::Rollers::Standby{});
}

void contingencies() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    chassis->toggleHold();
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
    match->setColor((match->getColor() == Color::Red) ? Color::Blue : Color::Red);
}