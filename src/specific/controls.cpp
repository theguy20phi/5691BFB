#include "controls.hpp"

void chassisControls() {
  chassis->setState(Chassis::Control{master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 100,
                                     master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) * 100,
                                     master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 100});
}

void rollerControls() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    shiftedRollerControls();
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    rollers->setState(Rollers::Intake{});
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    rollers->setState(Rollers::Outtake{});
  else
    rollers->setState(Rollers::Standby{});
  rollers->slowRollers(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
}

void shiftedRollerControls() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    rollers->setState(Rollers::SimpleCycle{});
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    rollers->setState(Rollers::FastShoot{});
  else
    rollers->setState(Rollers::Shoot{});
}

void contingencies() {
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    chassis->toggleHold();
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
    match->setColor(((match->getColor() == bfb::Color::Red) ? bfb::Color::Blue : bfb::Color::Red));
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    rollers->setState(Rollers::Cycle{match->getColor()});
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    rollers->setState(Rollers::Eject{});
}