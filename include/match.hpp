#pragma once

#include "main.h"

enum class Color { Red, Blue };

enum class Routine { Left, LeftMiddle, RightMiddle, Right, Row, None };

class Match {
  public:
  Match();
  void update();
  Routine getRoutine() const;
  Color getColor() const;
  void setRoutine(const Routine &iRoutine);
  void setColor(const Color &iColor);

  private:
  Color color{Color::Red};
  Routine routine{Routine::Left};
  pros::ADIPotentiometer routineSelector{5};
  pros::ADIPotentiometer colorSelector{6};
};