#include "autonMacros.hpp"

bool chassisStandby() {
  return std::holds_alternative<Chassis::Standby>(chassis->getState());
}

bool isBlue() {
  return rollers->isInEjector() && rollers->getBallColor() == bfb::Color::Blue;
}

bool isRed() {
  return rollers->isInEjector() && rollers->getBallColor() == bfb::Color::Red;
}

bool isInEjector() {
  return rollers->isInEjector();
}

bool isNotInEjector() {
  return !rollers->isInEjector();
}