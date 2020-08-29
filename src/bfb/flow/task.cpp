#include "task.hpp"

namespace bfb {
Task::Task(std::uint32_t iPriority) : priority(iPriority) {
}

void Task::start() {
  if (!task) {
    taskLog.log("Task started.", {});
    task = std::make_unique<pros::Task>(
      [this]() {
        for (;;) {
          this->step();
          wait(Wait::generalDelay);
        }
      },
      priority);
  }
}

void Task::stop() {
  if (task) {
    taskLog.log("Task ended.", {});
    task = nullptr;
  }
}

Logger<Task> Task::taskLog{};

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