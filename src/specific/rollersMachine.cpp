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
  if (indexer.get_value() < indexerThreshold) {
    lowerBigRoller.move_velocity(0);
    upperBigRoller.move_velocity(0);
  } else {
    lowerBigRoller.move_velocity(600);
    upperBigRoller.move_velocity(600);
  }
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
}

void RollersMachine::behavior(const States::Rollers::Outtake &outtake) {
  lowerBigRoller.move_velocity(-600);
  upperBigRoller.move_velocity(-600);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}

void RollersMachine::behavior(const States::Rollers::Shoot &shoot) {
  lowerBigRoller.move_velocity(600);
  upperBigRoller.move_velocity(600);
  leftSideRoller.move_velocity(0);
  rightSideRoller.move_velocity(0);
}

void RollersMachine::behavior(const States::Rollers::Cycle &cycle) {
  lowerBigRoller.move_velocity(600);
  leftSideRoller.move_velocity(600);
  rightSideRoller.move_velocity(600);
  if (indexer.get_value() < indexerThreshold) {
    if (visionSensor.get_by_size(0).signature == 1) { // blue
      if (cycle.color == Color::Red) {
        upperBigRoller.move_velocity(-600);
      } else
        upperBigRoller.move_velocity(600);
    } else { // red
      if (cycle.color == Color::Blue) {
        upperBigRoller.move_velocity(-600);
      } else
        upperBigRoller.move_velocity(600);
    }
  } else // nothing
    upperBigRoller.move_velocity(600);
}

void RollersMachine::behavior(const States::Rollers::FastShoot &fastShoot) {
  lowerBigRoller.move_velocity(600);
  upperBigRoller.move_velocity(600);
  leftSideRoller.move_velocity(-600);
  rightSideRoller.move_velocity(-600);
}