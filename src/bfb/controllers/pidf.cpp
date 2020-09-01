#include "pidf.hpp"

namespace bfb {
Pidf::Pidf(const PidfGains &iGains, std::unique_ptr<okapi::SettledUtil> iSettledChecker)
  : gains(iGains), settledChecker(std::move(iSettledChecker)) {
  pidfLog.log("Pidf created.", {});
}

double Pidf::calculate(double state) {
  if (pros::millis() - lastTime < Wait::generalDelay)
    return output;
  lastTime = pros::millis();
  const double error{reference - state};
  settledChecker->isSettled(error);
  output = calculateP(error) + calculateI(error) + calculateD(state) + gains.f;
  return output;
}

double Pidf::calculateP(double error) {
  return gains.kP * error;
}

double Pidf::calculateI(double error) {
  I *= I_DECAY;
  I += error * gains.kI;
  if (previousSign != sign(error))
    I = 0;
  previousSign = sign(error);
  return I;
}

double Pidf::calculateD(double state) {
  const double D{previousState - state};
  previousState = state;
  return dFilter.filter(D) * gains.kD;
}

bool Pidf::isDone(double state) {
  return settledChecker->isSettled(reference - state);
}

void Pidf::reset() {
  reference = 0.0;
  output = 0.0;
  previousState = 0.0;
  I = 0.0;
  previousSign = 1;
  lastTime = pros::millis();
  settledChecker->reset();
  pidfLog.log("Pidf controller reset.", {});
}

Logger<Pidf> Pidf::pidfLog{};

#ifdef TESTING
DEFINE_TEST(pidfTest)
using namespace okapi;
Pidf testPidf{{2.0, 2.0, 2.0, 2.0}, createSettledUtil(0, 0, 0_ms)};
wait(100);
testPidf.setReference(12.0);
IS_EQUAL(testPidf.calculate(2.0), 40.0);
END_TEST
#endif
} // namespace bfb