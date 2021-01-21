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
} // namespace bfb