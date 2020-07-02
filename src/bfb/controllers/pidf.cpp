#include "pidf.hpp"

namespace bfb {
Pidf::Pidf(const PidfConstants &iConstants, const okapi::TimeUtil &iTimeUtil)
  : constants(iConstants), settledChecker(iTimeUtil.getSettledUtil()) {
}

void Pidf::setReference(double iReference) {
  reference = iReference;
}

double Pidf::step(double state) {
  double error{reference - state};
  double P{error * constants.kP};
  I *= I_DECAY;
  I += error * constants.kI;
  I = isAlmostZero(I, 0.05) ? 0.0 : I;
  double D{state - previousState};
  previousState = state;
  settledChecker->isSettled(error);
  output = P + I + D + constants.f;
  return output;
}

double Pidf::getOutput() const {
  return output;
}

bool Pidf::isSettled(double state) {
  return settledChecker->isSettled(reference - state);
}

void Pidf::reset() {
  reference = 0.0;
  output = 0.0;
  previousState = 0.0;
  I = 0.0;
  settledChecker->reset();
}

const double Pidf::I_DECAY{0.95};
} // namespace bfb