/**
 * A simple interface for controllers.
 *
 * @author Braden Pierce
 */
#pragma once

namespace bfb {
class Controller {
  public:
  virtual ~Controller() = default;

  /**
   * Sets reference for the controller.
   *
   * @param iReference The new reference for the controller.
   */
  virtual void setReference(const double iReference) = 0;

  /**
   * Gets the current reference for the controller.
   *
   * @return Returns the current reference.
   */
  virtual double getReference() const = 0;

  /**
   * Goes through one step of the controller.
   *
   * @param state The current state of the controlled system.
   * @return The output of the controller.
   */
  virtual double step(const double state) = 0;

  /**
   * Gets the output of the controller.
   *
   * @return Returns the output of the controller.
   */
  virtual double getOutput() const = 0;

  /**
   * Gets if the controller is settled.
   *
   * @param state The current state of the controlled system.
   * @return If the controller is settled.
   */
  virtual bool isSettled(const double state) = 0;

  /**
   * Resets the internal state of the controller.
   */
  virtual void reset() = 0;
};
} // namespace bfb