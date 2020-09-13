#include "task.hpp"

namespace bfb {
Task::Task(std::uint32_t iPriority) : priority(iPriority) {
}

void Task::step() {
}

void Task::start() {
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

void Task::stop() {
  taskLog.log("Task stopped.", {});
  task = nullptr;
}

Logger<Task> Task::taskLog{};

} // namespace bfb