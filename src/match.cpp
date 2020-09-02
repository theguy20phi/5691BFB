#include "match.hpp"

Routine::Routine(const std::function<void()> &iRoutine, const Info &iInfo)
  : routine(iRoutine), info(iInfo) {
}

void Routine::execute() {
  routine();
}

Routine::Info Routine::getInfo() const {
  return info;
}

Match::Match(const std::array<Routine, 12> &iRoutines) : routines(iRoutines) {
  routineSelector.calibrate();
  colorSelector.calibrate();
  update();
}

void Match::update() {
  int tempIndex{0};
  if (colorSelector.get_value_calibrated() > 2048)
    tempIndex += 6;
  tempIndex += routineSelector.get_value_calibrated() / 683;
  index = tempIndex;
  color = getRoutine().getInfo().color;
}

Routine Match::getRoutine() const {
  return routines[index];
}

Color Match::getColor() const {
  return color;
}

void Match::setRoutine(int iIndex) {
  index = iIndex;
}

void Match::setColor(const Color &iColor) {
  color = iColor;
}