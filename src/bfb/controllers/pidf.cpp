#include "pidf.hpp"

namespace bfb {
Pidf::Pidf(const PidfGains &iGains, std::unique_ptr<okapi::SettledUtil> iSettledChecker)
  : gains(iGains), settledChecker(std::move(iSettledChecker)) {
}

void Pidf::setReference(const double iReference) {
  reference = iReference;
}

double Pidf::step(const double state) {
  double error{reference - state};
  double P{error * gains.kP};
  I *= I_DECAY;
  I += error * gains.kI;
  I = isAlmostZero(I, 0.05) ? 0.0 : I;
  double D{previousState - state};
  previousState = state;
  settledChecker->isSettled(error);
  output = P + I + D + gains.f;
  return output;
}

double Pidf::getOutput() const {
  return output;
}

bool Pidf::isSettled(const double state) {
  return settledChecker->isSettled(reference - state);
}

void Pidf::reset() {
  reference = 0.0;
  output = 0.0;
  previousState = 0.0;
  I = 0.0;
  settledChecker->reset();
}

#ifdef TESTING
DEFINE_TEST(pidfTest)
using namespace okapi;
Pidf testPidf{{2.0, 2.0, 2.0, 2.0},
              std::make_unique<okapi::SettledUtil>(std::make_unique<okapi::Timer>(), 10, 1, 0_ms)};
testPidf.setReference(12.0);
IS_EQUAL(testPidf.step(2.0), 38.0)
END_TEST
#endif
} // namespace bfb