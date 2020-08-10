#include "task.hpp"

namespace bfb {
template <std::uint32_t priority> Logger<Task<priority>> Task<priority>::taskLog{};
#ifdef TESTING
void TaskTestClass::step() {
  if (thing)
    thing = 0;
  else
    thing = 1;
}

DEFINE_TEST(taskTest)
TaskTestClass test;
test.start();
test.start();
pros::delay(50);
test.stop();
test.stop();
END_TEST
#endif
} // namespace bfb