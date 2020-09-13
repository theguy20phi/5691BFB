/**
 * @file roller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

namespace States {
namespace Rollers {
struct Standby {};
struct Intake {};
struct Outtake {};
struct Shoot {};
struct Cycle {};
struct FastShoot {};
using RollersStates = std::variant<Standby, Intake, Outtake, Shoot, Cycle, FastShoot>;
} // namespace Rollers
} // namespace States

class RollersMachine : public bfb::StateMachine<RollersMachine, States::Rollers::RollersStates> {
  public:
  RollersMachine(const States::Rollers::RollersStates &iState);
  void behavior(const States::Rollers::Standby &standby);
  void behavior(const States::Rollers::Intake &intake);
  void behavior(const States::Rollers::Outtake &outtake);
  void behavior(const States::Rollers::Shoot &shoot);
  void behavior(const States::Rollers::Cycle &cycle);
  void behavior(const States::Rollers::FastShoot &fastShoot);

  private:
  const int indexerThreshold{2000};
  pros::ADILineSensor indexer{'G'};
  pros::ADILightSensor colorSensor{'H'};
  pros::Motor lowerBigRoller{5, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
  pros::Motor upperBigRoller{6, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
  pros::Motor leftSideRoller{9, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
  pros::Motor rightSideRoller{10, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
};