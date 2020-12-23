/**
 * @file chassisMachine.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

namespace Chassis {
/**
 * @brief Standby state.
 *
 */
struct Standby {};

/**
 * @brief Control state, made of three integers to represent forward, strafe, and turn commands.
 *
 */
struct Control {
  int forward;
  int strafe;
  int turn;
};

/**
 * @brief MoveTo State, made of two QLengths (x and y), and a QAngle (h).
 *
 */
struct MoveTo {
  okapi::QLength x;
  okapi::QLength y;
  okapi::QAngle h;
};

using ChassisStates = std::variant<Standby, Control, MoveTo>;
} // namespace Chassis

/**
 * @brief Represents the entire chassis of the robot and is responsible for its behavior during
 * auton and driving.
 *
 */
class ChassisMachine : public bfb::StateMachine<ChassisMachine, Chassis::ChassisStates> {
  public:
  /**
   * @brief Construct a new Chassis Machine object
   *
   * @param iState
   */
  ChassisMachine(const Chassis::ChassisStates &iState);
  void behavior(const Chassis::Standby &standby);
  void behavior(const Chassis::Control &control);
  void behavior(const Chassis::MoveTo &moveTo);

  /**
   * @brief Resets the internal pose of the odometry.
   *
   * @param iX
   * @param iY
   * @param iH
   */
  void reset(okapi::QLength iX = 0.0_in, okapi::QLength iY = 0.0_in, okapi::QAngle iH = 0.0_rad);

  /**
   * @brief Gets the x value of the bot.
   *
   * @return okapi::QLength
   */
  okapi::QLength X() const;

  /**
   * @brief Gets the y value of the bot.
   *
   * @return okapi::QLength
   */
  okapi::QLength Y() const;

  /**
   * @brief Gets the h value of the bot.
   *
   * @return okapi::QAngle
   */
  okapi::QAngle H() const;

  /**
   * @brief Toggle if the robot is holding its position.
   *
   */
  void toggleHold();

  /**
   * @brief Set the robot to hold its position.
   *
   */
  void hold();

  /**
   * @brief Set the robot to coast when braking.
   *
   */
  void coast();

  private:
  void controlDrive(double forward, double strafe, double turn);
  void moveVelocity(double forward, double strafe, double turn);
  void moveVoltage(double forward, double strafe, double turn);
  void planStep(const Chassis::MoveTo &moveTo);
  void brake();

  private:
  bfb::CrossOdometry odometry{bfb::Odometer{pros::ADIEncoder{8, 7, true}, -0.5, 8.845},
                              bfb::Odometer{pros::ADIEncoder{5, 6, true}, 0.5, 8.845},
                              bfb::IMU{{13, 14, 15}}};
  pros::Motor lFWheel{11};
  pros::Motor lBWheel{20};
  pros::Motor rFWheel{12, true};
  pros::Motor rBWheel{18, true};
  const double deadband{100.0};
  bfb::Pidf xPidf{{1550.0, 21.0}, bfb::createSettledUtil(1.0, 0.15)};
  bfb::Pidf yPidf{{1550.0, 21.0}, bfb::createSettledUtil(1.0, 0.15)};
  bfb::Pidf hPidf{{37250.0, 400.0}, bfb::createSettledUtil(0.04, 0.004)};
};