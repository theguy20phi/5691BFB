#include "tbh.hpp"

namespace bfb {
Tbh::Tbh(double iGain, std::unique_ptr<okapi::SettledUtil> iSettledChecker)
  : gain(iGain), settledChecker(std::move(iSettledChecker)) {
  tbhLog.log("Tbh created.", {});
}

double Tbh::calculate(double state) {
  if (pros::millis() - lastTime < Wait::generalDelay)
    return output;
  lastTime = pros::millis();
  double error{reference - state};
  output += gain * error;
  takeBackHalf(sign(error));
  settledChecker->isSettled(error);
  return output;
}

void Tbh::takeBackHalf(int errorSign) {
  if (errorSign != previousErrorSign) {
    output = 0.5 * (output + tbh);
    tbh = output;
    previousErrorSign = errorSign;
  }
}

bool Tbh::isDone(double state) {
  settledChecker->isSettled(reference - state);
}

void Tbh::reset() {
  output = 0.0;
  reference = 0.0;
  tbh = 0.0;
  previousErrorSign = 0.0;
  settledChecker->reset();
  tbhLog.log("Tbh reset.", {});
}

Logger<Tbh> Tbh::tbhLog{};

#ifdef TESTING
DEFINE_TEST(tbhTest)
using namespace okapi;
Tbh testTbh{{2.0},
            std::make_unique<okapi::SettledUtil>(std::make_unique<okapi::Timer>(), 10, 1, 0_ms)};
wait(100);
testTbh.setReference(10.0);
IS_EQUAL(testTbh.calculate(2.0), 8.0);
END_TEST
#endif
} // namespace bfb