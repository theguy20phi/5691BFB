#include "wait.hpp"

namespace bfb {
void waitUntil(const std::function<bool()> &condition, const int maxDelay) {
  std::uint32_t timeout{pros::millis() + maxDelay};
  auto timedCondition = [condition, timeout]() -> bool {
    return condition() || pros::millis() >= timeout;
  };
  waitUntil(timedCondition);
}

void waitUntil(const std::function<bool()> &condition) {
  while (!condition())
    wait(vex_delay);
}

void wait(const int ms) {
  std::uint32_t now{pros::millis()};
  pros::Task::delay_until(&now, ms);
}

#ifdef TESTING
DEFINE_TEST(waitUntilWithTimeoutTest)
auto neverPassingLambda = []() -> bool {};
//if it gets past this, the test has passed
waitUntil(neverPassingLambda, 500);
END_TEST

DEFINE_TEST(waitUntilTest)
int testVar{0};
auto testLambda = [&testVar]() -> bool {
  if (testVar == 10)
    return true;
  testVar++;
};
waitUntil(testLambda);
IS_EQUAL(testVar, 10)
END_TEST
#endif
} // namespace bfb