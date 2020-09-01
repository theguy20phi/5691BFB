#include "task.hpp"

namespace bfb {
Task::Task(std::uint32_t iPriority) : priority(iPriority) {
}

void Task::step() {
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
      "BFB TASK");
  }
}

Logger<Task> Task::taskLog{};

} // namespace bfb