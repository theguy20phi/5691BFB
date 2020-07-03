#include "tbh.hpp"

namespace bfb {
Tbh::Tbh(const double iGain, std::unique_ptr<okapi::SettledUtil> iSettledChecker)
  : gain(iGain), settledChecker(std::move(iSettledChecker)) {
}

void Tbh::setReference(const double iReference) {
  reference = iReference;
}

double Tbh::step(const double state) {
  double error{reference - state};
  int errorSign{sign(error)};
  output += gain * error;
  if (errorSign != previousErrorSign) {
    output = 0.5 * (output + tbh);
    tbh = output;
    previousErrorSign = errorSign;
  }
  settledChecker->isSettled(error);
  return output;
}

double Tbh::getOutput() const {
  return output;
}

bool Tbh::isSettled(const double state) {
  settledChecker->isSettled(reference - state);
}

void Tbh::reset() {
  output = 0.0;
  reference = 0.0;
  tbh = 0.0;
  previousErrorSign = 0.0;
  settledChecker->reset();
}

#ifdef TESTING
DEFINE_TEST(tbhTest)
using namespace okapi;
Tbh testTbh{{2.0},
            std::make_unique<okapi::SettledUtil>(std::make_unique<okapi::Timer>(), 10, 1, 0_ms)};
testTbh.setReference(10.0);
IS_EQUAL(testTbh.step(2.0), 8.0)
END_TEST
#endif
} // namespace bfb