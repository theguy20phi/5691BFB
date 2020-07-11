#include "wait.hpp"

namespace bfb {
void waitUntil(const std::function<bool()> &condition) {
  while (!condition())
    wait(vex_delay);
}

void wait(const int ms) {
  std::uint32_t now{pros::millis()};
  pros::Task::delay_until(&now, ms);
}

#ifdef TESTING
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