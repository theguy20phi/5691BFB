/* -------------------------------------------------------------------------- */
/*                                   Set Up                                   */
/* -------------------------------------------------------------------------- */
#include "main.h"



void extraChecks() {
  if (master.get_battery_level() < 50)
    static bfb::Issue controllerLow{"CtrlLow", bfb::Severity::Medium};
  if (pros::battery::get_capacity() < 50)
    static bfb::Issue batteryLow{"BattLow", bfb::Severity::Medium};
}

void controllerGUITaskFn() {
  master.clear();
  for (;;) {
    if (!pros::competition::is_disabled()) {
      if (bfb::Issue::getIssueList().size() >= 1)
        master.print(0,
                     0,
                     "%s: %c                ",
                     bfb::Issue::getIssueList()[0].getDescription(),
                     bfb::Issue::getIssueList()[0].getSeverity().alpha);
      else 
        master.clear_line(0);
      bfb::wait(50);
      if (bfb::Issue::getIssueList().size() >= 2)
        master.print(1,
                     0,
                     "%s: %c                ",
                     bfb::Issue::getIssueList()[1].getDescription(),
                     bfb::Issue::getIssueList()[1].getSeverity().alpha);
      else
        master.clear_line(1);

      bfb::wait(50);
      if (bfb::Issue::getIssueList().size() >= 3)
        master.print(2,
                     0,
                     "%s: %c                ",
                     bfb::Issue::getIssueList()[2].getDescription(),
                     bfb::Issue::getIssueList()[2].getSeverity().alpha);
      else
        master.clear_line(2);
    } else {
      master.print(0, 0, "%s                ", match->getRoutine().getInfo().name);
      bfb::wait(50);
      master.print(1, 0, "%s                ", match->getRoutine().getInfo().description);
      bfb::wait(50);
      master.print(2, 0, "%s                ", match->getRoutine().getInfo().setup);
    }
    extraChecks();
    bfb::wait(50);
  }
}

LV_IMG_DECLARE(DOOM);
void doomScreen() {
  lv_obj_t *mainScreen = lv_obj_create(NULL, NULL);
  lv_obj_t *image = lv_img_create(mainScreen, NULL);
  lv_img_set_src(image, &DOOM);
  lv_scr_load(mainScreen);
}

void initialize() {
  rollers = std::make_unique<RollersMachine>(States::Rollers::Standby{});
  chassis = std::make_unique<ChassisMachine>(States::Chassis::Standby{});
  match = std::make_unique<Match>(std::array<Routine, 12>{redLeft,
                                                          redMidLeft,
                                                          redMidRight,
                                                          redRight,
                                                          redRow,
                                                          skills,
                                                          blueLeft,
                                                          blueMidLeft,
                                                          blueMidRight,
                                                          blueRight,
                                                          blueRow,
                                                          none});
  pros::Task controllerGUITask{controllerGUITaskFn};
  rollers->start();
  chassis->start();
  doomScreen();
}

void disabled() {
  rollers->setState(States::Rollers::Standby{});
  chassis->setState(States::Chassis::Standby{});
  for (;;) {
    match->update();
    bfb::wait(bfb::Wait::generalDelay);
  }
}

void competition_initialize() {
  for (;;) {
    match->update();
    bfb::wait(bfb::Wait::generalDelay);
  }
}

/* -------------------------------------------------------------------------- */
/*                                 Autonomous                                 */
/* -------------------------------------------------------------------------- */
void autonomous() {
  chassis->reset();
  match->getRoutine().execute();
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
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    chassis->toggleHold();
}

void opcontrol() {
  bfb::runTests();
  for (;;) {
    chassis->setState(
      States::Chassis::Control{master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 100,
                               master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) * 100,
                               master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 100});
    rollerControls();
    contingencies();
    bfb::wait(10);
  }
}
