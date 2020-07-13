/**
 * @file stateMachine.hpp
 * @author Braden Pierce
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/robot.hpp"
#include <memory>
#include <queue>
#include <typeinfo>

namespace bfb {
/**
 * @brief StateMachine implements a finite state machine. A standby state should be provided. A
 * StateMachine object can be limited to a certain type of state, via templating. If something else
 * needs to see the state of the machine, it should probably be a part of the machine.
 *
 * @tparam StateType
 */
template <typename StateType> class StateMachine final {
  public:
  /**
   * @brief Construct a new StateMachine object.
   *
   * @param iRobot
   * @param iStandbyState
   */
  StateMachine(const std::shared_ptr<Robot> &iRobot, const StateType &iStandbyState)
    : robot(iRobot), state(iStandbyState), standbyState(iStandbyState) {
  }

  /**
   * @brief Goes through one step of the StateMachine.
   *
   * @return bool
   */
  bool step() {
    if (state->step())
      return true;
    return false;
  }

  /**
   * @brief Sets the current state.
   *
   * @param newState
   */
  void setState(const StateType &newState) {
    state = newState;
  }

  /**
   * @brief Determines if the StateMachine's state is done.
   *
   * @return bool
   */
  bool isDone() {
    return step();
  }

  /**
   * @brief Resets the state to standby.
   * 
   */
  void standby() {
    state = standbyState;
  }

  /**
   * @brief Gets the state in string form. SHOULD ONLY BE USED FOR DEBUGGING.
   *
   * @return std::string
   */
  std::string toString() const {
    return typeid(*state).name();
  }

  private:
  std::shared_ptr<Robot> robot;
  StateType state;
  const StateType standbyState;
};
} // namespace bfb