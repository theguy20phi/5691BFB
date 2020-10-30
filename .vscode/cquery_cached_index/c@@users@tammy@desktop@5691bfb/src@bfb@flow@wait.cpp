#include "wait.hpp"

namespace bfb {
void waitUntil(const std::function<bool()> &condition, const int maxDelay) {
  std::uint32_t timeout{pros::millis() + maxDelay};
  waitUntil([condition, timeout]() { return condition() || pros::millis() >= timeout; });
}

void waitUntil(const std::function<bool()> &condition) {
  while (!condition())
    wait(Wait::generalDelay);
}

void wait(const int ms) {
  std::uint32_t now{pros::millis()};
  pros::Task::delay_until(&now, ms);
}

#ifdef TESTING
DEFINE_TEST(waitUntilWithTimeoutTest)
// if it gets past this, the test has passed
waitUntil([]() -> bool {}, 500);
END_TEST

DEFINE_TEST(waitUntilTest)
int testVar{0};
auto testLambda = [&testVar]() -> bool {
  if (testVar == 10)
    return true;
  testVar++;
  return false;
};
waitUntil(testLambda);
IS_EQUAL(testVar, 10);
END_TEST
#endif
} // namespace bfb