#include "gui.hpp"

void extraChecks() {
  if (master.get_battery_level() < 50)
    static bfb::Issue controllerLow{"CtrlLow", bfb::Severity::Medium};
  if (pros::battery::get_capacity() < 50)
    static bfb::Issue batteryLow{"BattLow", bfb::Severity::Medium};
  if (!pros::competition::is_connected())
    static bfb::Issue notConnected{"CompCtrl", bfb::Severity::Low};
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

void doomScreen() {
  lv_obj_t *mainScreen = lv_obj_create(NULL, NULL);
  lv_obj_t *image = lv_img_create(mainScreen, NULL);
  lv_img_set_src(image, &DOOM);
  lv_scr_load(mainScreen);
}