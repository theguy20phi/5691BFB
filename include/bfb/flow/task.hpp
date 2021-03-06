/**
 * @file task.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/logger.hpp"
#include "pros/rtos.hpp"
#include "wait.hpp"
#include <memory>

namespace bfb {
/**
 * @brief Allows an easy-to-use way to assign "give" (more like make) a class a task by inheriting
 * from this class.
 *
 */
class Task {
  public:
  /**
   * @brief Construct a new Task object
   *
   * @param iPriority
   */
  Task(std::uint32_t iPriority = TASK_PRIORITY_DEFAULT);

  /**
   * @brief Goes through one step of the Task. Should be overwritten. Should take and return
   * nothing.
   *
   */
  virtual void step();

  /**
   * @brief Starts the task.
   *
   */
  virtual void start() final;
  
  /**
   * @brief Stops the task.
   * 
   */
  virtual void stop() final;

  /**
   * @brief Logger object for Task.
   *
   */
  static Logger<Task> taskLog;

  protected:
  std::uint32_t priority;
  std::unique_ptr<pros::Task> task{nullptr};
};
} // namespace bfb