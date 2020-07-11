/**
 * @file controller.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

namespace bfb {
class Controller {
  public:
  virtual ~Controller() = default;

  /**
   * @brief Sets the reference for the controller.
   *
   * @param iReference
   */
  virtual void setReference(const double iReference) = 0;

  /**
   * @brief Gets the current reference for the controller.
   *
   * @return double
   */
  virtual double getReference() const = 0;

  /**
   * @brief Goes through one step of the controller.
   *
   * @param state
   * @return double
   */
  virtual double step(const double state) = 0;

  /**
   * @brief Gets the output of the controller.
   *
   * @return double
   */
  virtual double getOutput() const = 0;

  /**
   * @brief Gets if the controller is settled.
   *
   * @param state
   * @return bool
   */
  virtual bool isSettled(const double state) = 0;

  /**
   * @brief Resets the internal state of the controller.
   */
  virtual void reset() = 0;
};
} // namespace bfb