#include "chassisMachine.hpp"

ChassisMachine::ChassisMachine(const States::Chassis::ChassisStates &iState)
  : StateMachine(iState) {
  coast();
  odometry.start();
  odometry.reset(0_m, 0_m, 0_rad);
}

void ChassisMachine::behavior(const States::Chassis::Standby &standby) {
}

void ChassisMachine::behavior(const States::Chassis::Control &control) {
  controlDrive(control.forward, control.strafe, control.turn);
}

void ChassisMachine::behavior(const States::Chassis::MoveTo &moveTo) {
  const double xDist{getDistanceTo(odometry.H(), moveTo)};
  const double yDist{getDistanceTo(odometry.H() - 90_deg, moveTo)};
  const double hDist{moveTo.h.convert(okapi::radian) - odometry.H().convert(okapi::radian)};
  xPidf.calculate(xDist);
  yPidf.calculate(yDist);
  hPidf.calculate(hDist);
  controlDrive(xPidf.getOutput(), yPidf.getOutput(), hPidf.getOutput());
  if (xPidf.isDone(xDist) && yPidf.isDone(yDist) && hPidf.isDone(hDist))
    setState(States::Chassis::Standby{});
}

double ChassisMachine::getDistanceTo(const okapi::QAngle &h,
                                     const States::Chassis::MoveTo &moveTo) {
  // May need edge case for m if cos(h) == 0
  const double m{sin(h.convert(okapi::radian) / cos(h.convert(okapi::radian)))};
  const double bT{moveTo.y.convert(okapi::meter) - m * moveTo.x.convert(okapi::meter)};
  const double bR{odometry.Y().convert(okapi::meter) - m * odometry.X().convert(okapi::meter)};
  return fabs(bT - bR) / sqrt(m * m + 1);
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

void ChassisMachine::controlDrive(double forward, double strafe, double turn) {
  rFSlew.slew(forward + strafe - turn);
  rBSlew.slew(forward - strafe - turn);
  if (forward + strafe + turn < deadband) {
    lFWheel.move_velocity(0);
    lBWheel.move_velocity(0);
    rFWheel.move_velocity(0);
    rBWheel.move_velocity(0);
  } else {
    lFWheel.move_voltage(forward - strafe + turn);
    lBWheel.move_voltage(forward + strafe + turn);
    rFWheel.move_voltage(rFSlew.getValue());
    rBWheel.move_voltage(rBSlew.getValue());
  }
}