/**
 * @file roller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

enum class Color;

namespace States {
namespace Rollers {
/**
 * @brief The Standby state for the rollers.
 *
 */
struct Standby {};

/**
 * @brief The Intake state for the rollers.
 *
 */
struct Intake {};

/**
 * @brief The Outtake state for the rollers.
 *
 */
struct Outtake {};

/**
 * @brief The Shoot state for the rollers.
 *
 */
struct Shoot {};

/**
 * @brief The Cycle state for the rollers, able to change the desired color on the fly.
 *
 */
struct Cycle {
  Color color;
};

/**
 * @brief The FastShoot state for the rollers (outtake side rollers while shooting).
 *
 */
struct FastShoot {};
using RollersStates = std::variant<Standby, Intake, Outtake, Shoot, Cycle, FastShoot>;
} // namespace Rollers
} // namespace States

class RollersMachine : public bfb::StateMachine<RollersMachine, States::Rollers::RollersStates> {
  public:
  /**
   * @brief Construct a new Rollers Machine object.
   * 
   * @param iState 
   */
  RollersMachine(const States::Rollers::RollersStates &iState);
  
  void behavior(const States::Rollers::Standby &standby);
  void behavior(const States::Rollers::Intake &intake);
  void behavior(const States::Rollers::Outtake &outtake);
  void behavior(const States::Rollers::Shoot &shoot);
  void behavior(const States::Rollers::Cycle &cycle);
  void behavior(const States::Rollers::FastShoot &fastShoot);

  private:
  void cycleDecision(const States::Rollers::Cycle &cycle);

  private:
  const int threshold{250};
  pros::ADIUltrasonic indexerSensor{'E', 'F'};
  pros::Vision visionSensor{20};
  pros::ADIUltrasonic shootingSensor{'G', 'H'};
  pros::Motor lowerBigRoller{5, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, false};
  pros::Motor upperBigRoller{6, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, true};
  pros::Motor leftSideRoller{9, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
  pros::Motor rightSideRoller{10, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06};
};