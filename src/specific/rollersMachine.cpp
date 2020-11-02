#include "rollersMachine.hpp"

RollersMachine::RollersMachine(const States::Rollers::RollersStates &iState)
  : StateMachine(iState) {
  lowerBigRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  upperBigRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  leftSideRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  rightSideRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void RollersMachine::behavior(const States::Rollers::Standby &standby) {
  lowerBigRoller.move_velocity(0);
  upperBigRoller.move_velocity(0);
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::behavior(const States::Rollers::Intake &intake) {
  intakeDecision();
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::intakeDecision() {
  if (shootingSensor.get_value() < threshold)
    upperBigRoller.move_velocity(0);
  else
    upperBigRoller.move_velocity(185);
  if (indexerSensor.get_value() < threshold)
    lowerBigRoller.move_velocity(0);
  else
    lowerBigRoller.move_velocity(400);
}

void RollersMachine::behavior(const States::Rollers::Outtake &outtake) {
  lowerBigRoller.move_velocity(-600);
  upperBigRoller.move_velocity(-600);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::behavior(const States::Rollers::Shoot &shoot) {
  lowerBigRoller.move_velocity(power);
  upperBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::behavior(const States::Rollers::Cycle &cycle) {
  lowerBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
  cycleDecision(cycle);
}

void RollersMachine::cycleDecision(const States::Rollers::Cycle &cycle) {
  std::cout << colorSensor.get_hue() << std::endl;
  if (indexerSensor.get_value() < threshold) {
    if(bfb::isAlmostEqual(colorSensor.get_hue(), blueHue, 15)) {
      if (cycle.color == Color::Red) {
        upperBigRoller.move_velocity(-power);
        bfb::wait(300);
      } else {
        upperBigRoller.move_velocity(power);
      }
    } else { // red
      if (cycle.color == Color::Blue) {
        upperBigRoller.move_velocity(-power);
        bfb::wait(400);
      } else {
        upperBigRoller.move_velocity(power);
      }
    }
  } else { // nothing
    upperBigRoller.move_velocity(power);
  }
}

void RollersMachine::behavior(const States::Rollers::FastShoot &fastShoot) {
  lowerBigRoller.move_velocity(power);
  upperBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::slowRollers(bool isMiddle) {
  if (isMiddle)
    power = 400;
  else
    power = 600;
}