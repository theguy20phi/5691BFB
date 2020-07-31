#include "task.hpp"

namespace bfb {
#ifdef TESTING
void TaskTestClass::step() {
  if (thing)
    thing = 0;
  else
    thing = 1;
  pros::delay(10);
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