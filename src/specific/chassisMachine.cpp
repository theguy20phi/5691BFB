#include "chassisMachine.hpp"

ChassisMachine::ChassisMachine(const States::Chassis::ChassisStates &iState)
  : StateMachine(iState) {
  coast();
  odometry.start();
  odometry.reset();
}

void ChassisMachine::behavior(const States::Chassis::Standby &standby) {
  brake();
}

void ChassisMachine::behavior(const States::Chassis::Control &control) {
  controlDrive(control.forward, control.strafe, control.turn);
}

void ChassisMachine::behavior(const States::Chassis::MoveTo &moveTo) {
  updatePids(moveTo);
  controlDrive(yPidf.getOutput(), xPidf.getOutput(), hPidf.getOutput());
}

void ChassisMachine::controlDrive(double forward, double strafe, double turn) {
  updateSlewRates(forward, strafe, turn);
  if (fabs(forward + strafe + turn) < deadband)
    brake();
  else
    move();
}

void ChassisMachine::updateSlewRates(double forward, double strafe, double turn) {
  lFSlew.slew(forward + strafe + turn);
  lBSlew.slew(forward - strafe + turn);
  rFSlew.slew(forward - strafe - turn);
  rBSlew.slew(forward + strafe - turn);
}

void ChassisMachine::brake() {
  lFWheel.move_velocity(0);
  lBWheel.move_velocity(0);
  rFWheel.move_velocity(0);
  rBWheel.move_velocity(0);
}

void ChassisMachine::move() {
  lFWheel.move_voltage(lFSlew.getValue());
  lBWheel.move_voltage(lBSlew.getValue());
  rFWheel.move_voltage(rFSlew.getValue());
  rBWheel.move_voltage(rBSlew.getValue());
}

void ChassisMachine::updatePids(const States::Chassis::MoveTo &moveTo) {
  const double xDiff{(odometry.getPose().X - moveTo.x).convert(okapi::meter)};
  const double yDiff{(odometry.getPose().Y - moveTo.y).convert(okapi::meter)};
  const double distance{sqrt(xDiff * xDiff + yDiff * yDiff)};
  const double direction{odometry.getPose().H.convert(okapi::radian) +
                         odometry.getPose().W.convert(okapi::radps) *
                           (bfb::Wait::generalDelay / 2000.0) +
                         atan2(yDiff, xDiff)};
  double xDistance{distance * cos(direction)};
  double yDistance{distance * sin(direction)};
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
