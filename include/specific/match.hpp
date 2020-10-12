/**
 * @file match.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include "main.h"

/**
 * @brief The two colors the robot can be.
 *
 */
enum class Color { Red, Blue };

/**
 * @brief Represents a autonomous routine abstractly.
 *
 */
class Routine {
  public:
  /**
   * @brief Information about the Routine.
   *
   */
  struct Info {
    Color color;
    std::string name;
    std::string description;
    std::string setup;
  };

  /**
   * @brief Construct a new Routine object.
   *
   * @param iRoutine
   * @param iInfo
   */
  Routine(const std::function<void()> &iRoutine, const Info &iInfo);

  /**
   * @brief Executes the autonomous routine.
   *
   */
  void execute();

  /**
   * @brief Gets the information about the autonomous routine (largely for the controller GUI).
   *
   * @return Info
   */
  Info getInfo() const;

  private:
  std::function<void()> routine;
  const Info info;
};

/**
 * @brief Represents the information about the match as a whole.
 *
 */
class Match {
  public:
  /**
   * @brief Construct a new Match object.
   *
   * @param iRoutines
   */
  Match(const std::array<Routine, 12> &iRoutines);

  /**
   * @brief Updates which autonomous routine is selected.
   * 
   */
  void update();

  /**
   * @brief Get the routine.
   * 
   * @return Routine 
   */
  Routine getRoutine() const;

  /**
   * @brief Get the color.
   * 
   * @return Color 
   */
  Color getColor() const;

  /**
   * @brief Set which routine is to be done.
   * 
   * @param iIndex 
   */
  void setRoutine(int iIndex);

  /**
   * @brief Set the color of the robot.
   * 
   * @param iColor 
   */
  void setColor(const Color &iColor);

  private:
  pros::ADIPotentiometer routineSelector{'G'};
  pros::ADIPotentiometer colorSelector{'H'};
  std::array<Routine, 12> routines;
  int index{0};
  Color color;
};
