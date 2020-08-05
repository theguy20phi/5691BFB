/**
 * @file controller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/logger.hpp"

namespace bfb {
class Controller {
  public:
  virtual ~Controller() = default;

  /**
   * @brief Sets the reference for the controller.
   *
   * @param iReference
   */
  virtual void setReference(double iReference);

  /**
   * @brief Gets the current reference for the controller.
   *
   * @return double
   */
  virtual double getReference() const;

  /**
   * @brief Goes through one step of the controller.
   *
   * @param state
   * @return double
   */
  virtual double calculate(double state) = 0;

  /**
   * @brief Gets the output of the controller.
   *
   * @return double
   */
  virtual double getOutput() const;

  /**
   * @brief Gets if the controller is settled.
   *
   * @param state
   * @return bool
   */
  virtual bool isDone(double state) = 0;

  /**
   * @brief Resets the internal state of the controller.
   */
  virtual void reset() = 0;

  /**
   * @brief Logger object for Controller.
   *
   */
  static Logger controllerLog;

  protected:
  double output{0.0};
  double reference{0.0};
};
} // namespace bfb