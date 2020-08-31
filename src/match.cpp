#include "match.hpp"

Match::Match() {
  routineSelector.calibrate();
  colorSelector.calibrate();
}

void Match::update() {
  if (routineSelector.get_value_calibrated() < 682)
    routine = Routine::Left;
  else if (routineSelector.get_value_calibrated() >= 682 &&
           routineSelector.get_value_calibrated() < 1364)
    routine = Routine::LeftMiddle;
  else if (routineSelector.get_value_calibrated() >= 1364 &&
           routineSelector.get_value_calibrated() < 2046)
    routine = Routine::RightMiddle;
  else if (routineSelector.get_value_calibrated() >= 2046 &&
           routineSelector.get_value_calibrated() < 2728)
    routine = Routine::Right;
  else if (routineSelector.get_value_calibrated() >= 2728 &&
           routineSelector.get_value_calibrated() < 3410)
    routine = Routine::Row;
  else
    routine = Routine::None;

  if (colorSelector.get_value_calibrated() < 2048)
    color = Color::Blue;
  else
    color = Color::Red;
}

Routine Match::getRoutine() const {
  return routine;
}

Color Match::getColor() const {
  return color;
}

void Match::setRoutine(const Routine &iRoutine) {
  routine = iRoutine;
}

void Match::setColor(const Color &iColor) {
  color = iColor;
}