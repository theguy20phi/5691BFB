#include "rollersMachine.hpp"

RollersMachine::RollersMachine(const Rollers::RollersStates &iState)
  : StateMachine(iState) {
  lowerBigRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  upperBigRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  leftSideRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  rightSideRoller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  colorSensor.set_led_pwm(100);
  colorSensor.disable_gesture();
}

void RollersMachine::behavior(const Rollers::Standby &standby) {
  lowerBigRoller.move_velocity(0);
  upperBigRoller.move_velocity(0);
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::behavior(const Rollers::Intake &intake) {
  intakeDecision();
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::intakeDecision() {
  if (indexerSensor.get_value() < threshold) {
    upperBigRoller.move_velocity(0);
    lowerBigRoller.move_velocity(0);
  } else {
    upperBigRoller.move_velocity(0);
    lowerBigRoller.move_velocity(400);
  }
}

void RollersMachine::behavior(const Rollers::Outtake &outtake) {
  lowerBigRoller.move_velocity(-600);
  upperBigRoller.move_velocity(-600);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::behavior(const Rollers::Shoot &shoot) {
  lowerBigRoller.move_velocity(150);
  upperBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::behavior(const Rollers::Cycle &cycle) {
  if (!isInEjector()) {
    upperBigRoller.move_velocity(100);
    lowerBigRoller.move_velocity(400);
    leftSideRoller.move_velocity(600);
    rightSideRoller.move_velocity(600);
  } else
    cycleDecision(cycle);
}

void RollersMachine::behavior(const Rollers::Eject &eject) {
  lowerBigRoller.move_velocity(600);
  upperBigRoller.move_velocity(-600);
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::behavior(const Rollers::SimpleCycle &simpleCycle) {
  lowerBigRoller.move_velocity(power);
  upperBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::behavior(const Rollers::Detach &detach) {
  lowerBigRoller.move_velocity(0);
  upperBigRoller.move_velocity(0);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::behavior(const Rollers::Hold &hold) {
  lowerBigRoller.move_velocity(0);
  upperBigRoller.move_velocity(0);
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::cycleDecision(const Rollers::Cycle &cycle) {
  behavior(Rollers::Intake{});
  bfb::wait(300);
  lowerBigRoller.move_velocity(100);
  if (getBallColor() != cycle.color) {
    upperBigRoller.move_velocity(-600);
    bfb::wait(350);
  } else {
    upperBigRoller.move_velocity(600);
    bfb::wait(450);
  }
}

bool RollersMachine::isInEjector() {
  return indexerSensor.get_value() < threshold;
}

bfb::Color RollersMachine::getBallColor() {
  if (colorSensor.get_rgb().blue > colorSensor.get_rgb().red)
    return bfb::Color::Blue;
  return bfb::Color::Red;
}

void RollersMachine::behavior(const Rollers::FastShoot &fastShoot) {
  lowerBigRoller.move_velocity(power);
  upperBigRoller.move_velocity(power);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::behavior(const Rollers::Cock &cock) {
  if(!isInEjector()) {
    upperBigRoller.move_velocity(-power);
    lowerBigRoller.move_velocity(-power);
  } else {
    upperBigRoller.move_velocity(0);
    lowerBigRoller.move_velocity(0);
  }
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::slowRollers(bool isMiddle) {
  if (isMiddle)
    power = 400;
  else
    power = 600;
}