/**
 * @file task.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/logger.hpp"
#include "bfb/debug/test.hpp"
#include "pros/rtos.hpp"
#include "wait.hpp"
#include <memory>

namespace bfb {
/**
 * @brief Allows an easy-to-use way to assign "give" (more like make) a class a task by inheriting
 * from this class.
 *
 * @tparam priority = TASK_PRIORITY_DEFAULT
 */
template <std::uint32_t priority = TASK_PRIORITY_DEFAULT> class Task {
  public:
  /**
   * @brief Goes through one step of the Task. Should be overwritten. Should take and return
   * nothing.
   *
   */
  virtual void step() = 0;

  /**
   * @brief Starts the task.
   *
   */
  virtual void start() final {
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

  /**
   * @brief Ends the task.
   *
   */
  virtual void stop() final {
    if (task) {
      taskLog.log("Task ended.", {});
      task = nullptr;
    }
  }

  /**
   * @brief Logger object for Task.
   *
   */
  static Logger<Task<priority>> taskLog;

  protected:
  std::unique_ptr<pros::Task> task{nullptr};
};

#ifdef TESTING
class TaskTestClass final : public Task<> {
  public:
  virtual void step() override;

  private:
  int thing{0};
};
DECLARE_TEST(taskTest);
#endif

} // namespace bfb