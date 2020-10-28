#include "chassisMachine.hpp"

ChassisMachine::ChassisMachine(const States::Chassis::ChassisStates &iState)
  : StateMachine(iState) {
  coast();
  odometry.start();
  odometry.reset();
}

void ChassisMachine::behavior(const States::Chassis::Standby &standby) {
  moveVelocity(0.0, 0.0, 0.0);
}

void ChassisMachine::behavior(const States::Chassis::Control &control) {
  controlDrive(control.forward, control.strafe, control.turn);
}

void ChassisMachine::behavior(const States::Chassis::MoveTo &moveTo) {
  planStep(moveTo);
  controlDrive(yPidf.getOutput(), xPidf.getOutput(), hPidf.getOutput());
}

void ChassisMachine::controlDrive(double forward, double strafe, double turn) {
  if (fabs(forward + strafe + turn) < deadband)
    moveVelocity(0.0, 0.0, 0.0);
  else
    moveVoltage(forward, strafe, turn);
}

void ChassisMachine::moveVelocity(double forward, double strafe, double turn) {
  lFWheel.move_velocity(forward + strafe + turn);
  lBWheel.move_velocity(forward - strafe + turn);
  rFWheel.move_velocity(forward - strafe - turn);
  rBWheel.move_velocity(forward + strafe - turn);
}

void ChassisMachine::moveVoltage(double forward, double strafe, double turn) {
  lFWheel.move_voltage(forward + strafe + turn);
  lBWheel.move_voltage(forward - strafe + turn);
  rFWheel.move_voltage(forward - strafe - turn);
  rBWheel.move_voltage(forward + strafe - turn);
}

void ChassisMachine::planStep(const States::Chassis::MoveTo &moveTo) {
  const double xDiff{(odometry.getPose().X - moveTo.x).convert(okapi::meter)};
  const double yDiff{(odometry.getPose().Y - moveTo.y).convert(okapi::meter)};
  const double distance{sqrt(xDiff * xDiff + yDiff * yDiff)};
  const double direction{odometry.getPose().H.convert(okapi::radian) + atan2(yDiff, xDiff)};
  const double xDistance{distance * cos(direction)};
  const double yDistance{distance * sin(direction)};
  const double hDistance{
    okapi::OdomMath::constrainAngle180(odometry.getPose().H - moveTo.h).convert(okapi::radian)};
  xPidf.calculate(xDistance);
  yPidf.calculate(yDistance);
  hPidf.calculate(hDistance);
  if (xPidf.isDone(xDistance) && yPidf.isDone(yDistance) && hPidf.isDone(hDistance))
    setState(States::Chassis::Standby{});
}

void ChassisMachine::reset(const bfb::CrossOdometry::Pose &iPose) {
  odometry.reset(iPose);
  setState(States::Chassis::Standby{});
}

void ChassisMachine::toggleHold() {
  if (lFWheel.get_brake_mode() == pros::E_MOTOR_BRAKE_COAST) {
    hold();
  } else {
    coast();
  }
}

void ChassisMachine::hold() {
  lFWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  lBWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rFWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rBWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void ChassisMachine::coast() {
  lFWheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lBWheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rFWheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rBWheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}