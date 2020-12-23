/**
 * @file roller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

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
  bfb::Color color;
};

/**
 * @brief The FastShoot state for the rollers (outtake side rollers while shooting).
 *
 */
struct FastShoot {};

/**
 * @brief Mostly for testing, just moves balls up without the use of sensors.
 *
 */
struct SimpleCycle {};

/**
 * @brief Manual Ejection state for the rollers.
 *
 */
struct Eject {};

/**
 * @brief The Detach state for the rollers (outtake side rollers).
 *
 */
struct Detach {};

/**
 * @brief The Hold state for the rollers (intake side rollers)
 * 
 */
struct Hold{};

using RollersStates =
  std::variant<Standby, Intake, Outtake, Shoot, Cycle, FastShoot, SimpleCycle, Eject, Detach, Hold>;
} // namespace Rollers

class RollersMachine : public bfb::StateMachine<RollersMachine, Rollers::RollersStates> {
  public:
  /**
   * @brief Construct a new Rollers Machine object.
   *
   * @param iState
   */
  RollersMachine(const Rollers::RollersStates &iState);

  void behavior(const Rollers::Standby &standby);
  void behavior(const Rollers::Intake &intake);
  void behavior(const Rollers::Outtake &outtake);
  void behavior(const Rollers::Shoot &shoot);
  void behavior(const Rollers::Cycle &cycle);
  void behavior(const Rollers::FastShoot &fastShoot);
  void behavior(const Rollers::SimpleCycle &simpleCycle);
  void behavior(const Rollers::Eject &eject);
  void behavior(const Rollers::Detach &detach);
  void behavior(const Rollers::Hold &hold);

  /**
   * Slows the roller for the middle goal.
   *
   * @param isMiddle
   */
  void slowRollers(bool isMiddle);

  /**
   * Tells if the ball is in front of the indexer.
   *
   * @return bool
   */
  bool isInEjector();

  /**
   * Gets the color of the ball in front of the optical sensor.
   *
   * @return bfb::Color
   */
  bfb::Color getBallColor();

  private:
  void intakeDecision();
  void cycleDecision(const Rollers::Cycle &cycle);

  private:
  const int threshold{2750};
  double power{600};
  const double blueHue{100};
  const double redHue{15};
  pros::ADIAnalogIn indexerSensor{'B'};
  pros::ADIAnalogIn shootingSensor{'A'};
  pros::Optical colorSensor{16};
  pros::Motor lowerBigRoller{10, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, false};
  pros::Motor upperBigRoller{9, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, true};
  pros::Motor leftSideRoller{1, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, true};
  pros::Motor rightSideRoller{6, pros::motor_gearset_e_t::E_MOTOR_GEARSET_06, false};
};