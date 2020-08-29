#include "main.h"

std::unique_ptr<RollersMachine> rollers;

void initialize() {
<<<<<<< HEAD
  rollers = std::make_unique<RollersMachine>(States::Rollers::Standby{});
=======
>>>>>>> 71095c11112a6361dd03636eb1ab18b512f9a1b1
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
}

void opcontrol() {
  bfb::runTests();
  okapi::Controller master_remote;
  std::shared_ptr<okapi::ChassisController> x_drive =
    okapi::ChassisControllerBuilder()
      .withMotors(1,  // Top left
                  -2, // Top right (reversed)
                  -3, // Bottom right (reversed)
                  4   // Bottom left
                  )
      .withDimensions(okapi::AbstractMotor::gearset::green,
                      {{3.25_in, 17.0_in}, okapi::imev5GreenTPR})
      .build();
  std::shared_ptr<okapi::Motor> upper_differential = std::make_shared<okapi::Motor>(
    5, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
  std::shared_ptr<okapi::Motor> lower_differential = std::make_shared<okapi::Motor>(
    6, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
  auto x_drive_model = std::dynamic_pointer_cast<okapi::XDriveModel>(x_drive->getModel());
  for (;;) {
    x_drive_model->xArcade(master_remote.getAnalog(okapi::ControllerAnalog::leftX),
                           master_remote.getAnalog(okapi::ControllerAnalog::leftY),
                           master_remote.getAnalog(okapi::ControllerAnalog::rightX));
    pros::Task::delay(10);
  }
}
