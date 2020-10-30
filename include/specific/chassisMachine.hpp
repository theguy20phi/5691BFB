/**
 * @file chassisMachine.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

namespace States {
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
  double x;
  double y;
  double h;
};

using ChassisStates = std::variant<Standby, Control, MoveTo>;
} // namespace Chassis
} // namespace States

/**
 * @brief Represents the entire chassis of the robot and is responsible for its behavior during
 * auton and driving.
 *
 */
class ChassisMachine : public bfb::StateMachine<ChassisMachine, States::Chassis::ChassisStates> {
  public:
  /**
   * @brief Construct a new Chassis Machine object
   *
   * @param iState
   */
  ChassisMachine(const States::Chassis::ChassisStates &iState);
  void behavior(const States::Chassis::Standby &standby);
  void behavior(const States::Chassis::Control &control);
  void behavior(const States::Chassis::MoveTo &moveTo);

  /**
   * @brief Resets the internal pose of the odometry.
   *
   * @param iX
   * @param iY
   * @param iH
   */
  void reset(double iX = 0.0, double iY = 0.0, double iH = 0.0);

  /**
   * @brief Gets the x value of the bot.
   *
   * @return double
   */
  double X() const;

  /**
   * @brief Gets the y value of the bot.
   *
   * @return double
   */
  double Y() const;

  /**
   * @brief Gets the h value of the bot.
   *
   * @return double
   */
  double H() const;

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
  void planStep(const States::Chassis::MoveTo &moveTo);
  void brake();

  private:
  bfb::CrossOdometry odometry{bfb::Odometer{pros::ADIEncoder{8, 7, true}, 0.0},
                              bfb::Odometer{pros::ADIEncoder{5, 6}, 0.0},
                              bfb::IMU{{13}}};
  pros::Motor lFWheel{11};
  pros::Motor lBWheel{20};
  pros::Motor rFWheel{12, true};
  pros::Motor rBWheel{18, true};
  const double deadband{100.0};
  bfb::Tbh xPidf{{27500.0}, bfb::createSettledUtil(0.05, 0.005)};
  bfb::Tbh yPidf{{27500.0}, bfb::createSettledUtil(0.05, 0.005)};
  bfb::Pidf hPidf{{7500.0, 0.0, 0.0, 0.0}, bfb::createSettledUtil(0.05, 0.005)};
};