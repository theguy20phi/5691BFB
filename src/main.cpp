/* -------------------------------------------------------------------------- */
/*                                   Set Up                                   */
/* -------------------------------------------------------------------------- */
#include "main.h"

std::unique_ptr<RollersMachine> rollers;
std::unique_ptr<ChassisMachine> chassis;
std::unique_ptr<Match> match;
pros::Controller master{pros::E_CONTROLLER_MASTER};
pros::Controller partner{pros::E_CONTROLLER_PARTNER};

auto chassisStandby = []() -> bool {
  return std::holds_alternative<States::Chassis::Standby>(chassis->getState());
};

LV_IMG_DECLARE(DOOM);
void doomScreen() {
  lv_obj_t *mainScreen = lv_obj_create(NULL, NULL);
  lv_obj_t *image = lv_img_create(mainScreen, NULL);
  lv_img_set_src(image, &DOOM);
  lv_scr_load(mainScreen);
}

void initialize() {
  doomScreen();
  rollers = std::make_unique<RollersMachine>(States::Rollers::Standby{});
  chassis = std::make_unique<ChassisMachine>(States::Chassis::Standby{});
  match = std::make_unique<Match>();
  rollers->start();
  chassis->start();
}

void disabled() {
  rollers->setState(States::Rollers::Standby{});
  chassis->setState(States::Chassis::Standby{});
  for (;;) {
    match->update();
    bfb::wait(10);
  }
}

void competition_initialize() {
  for (;;) {
    match->update();
    bfb::wait(10);
  }
}

/* -------------------------------------------------------------------------- */
/*                                 Autonomous                                 */
/* -------------------------------------------------------------------------- */
void autonomous() {
  chassis->setState(States::Chassis::MoveTo{1 * bfb::tile, 1 * bfb::tile, 180_deg});
  bfb::waitUntil(chassisStandby);
  if (match->getColor() == Color::Red) {
    switch (match->getRoutine()) {
    case Routine::Left:
      break;
    case Routine::LeftMiddle:
      break;
    case Routine::RightMiddle:
      break;
    case Routine::Right:
      break;
    case Routine::Row:
      break;
    case Routine::None:
      break;
    }
  } else {
    switch (match->getRoutine()) {
    case Routine::Left:
      break;
    case Routine::LeftMiddle:
      break;
    case Routine::RightMiddle:
      break;
    case Routine::Right:
      break;
    case Routine::Row:
      break;
    case Routine::None:
      break;
    }
  }
}

/* -------------------------------------------------------------------------- */
/*                                   Driver                                   */
/* -------------------------------------------------------------------------- */
/**
 * L1 = Intake
 * L2 = Outtake
 * R1 = Shoot
 * L1 + R1 = Cycle
 * L2 + R1 = Fast Shoot
 * N/A = Standby
 *
 */
void rollerControls() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
      rollers->setState(States::Rollers::Cycle{});
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
  if (partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    chassis->toggleHold();
}

void opcontrol() {
  bfb::runTests();
  for (;;) {
    chassis->setState(
      States::Chassis::Control{master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                               master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),
                               master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)});
    rollerControls();
    contingencies();
    bfb::wait(10);
  }
}
