/**
 * @file stateMachine.hpp
 * @author Braden Pierce
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/robot.hpp"
#include <functional>
#include <memory>

namespace bfb {
/**
 * @brief A generic StateMachine class with relatively-easy to create states and transitions
 * that do not violate OCP, are clearly defined and distinct from one another (where states
 * are more abstract representations for what the bot is doing, but transitions control behaviour),
 * where transitions can be paramaterized, where transitions can call upon the methods of the
 * StateMachine class, and where only certain states and transitions are deemed acceptable for use
 * by the StateMachine.
 *
 * States and transitions are to be defined by the user as such (replace "Mechanism" with specific
 * mechanism), examples for use are below:
 *
 * #include "stateMachine.hpp"
 *
 * enum class MechanismStates {
 *  Standby, //All states should probably have a standby state
 *  On,
 *  Off
 * };
 *
 * using MechanismTransition = Transition<MechanismStates>;
 *
 * MechanismTransition example(std::string arg, double otherArg) {
 *  return [=](StateMachine<MechanismStates> &machine) {
 *    machine.getRobot()->robotAction(arg);
 *    if(machine.getRobot()->robotSensor() < otherArg)
 *      machine.run(otherTransition());
 *    return Standby::On;
 *  };
 * }
 * @tparam State
 */
template <typename State> class StateMachine {
  public:
  // StateMachine isn't const, so transitions can call upon run to change the transition
  using Transition = std::function<State(StateMachine<State> &)>;

  /**
   * @brief Construct a new State Machine object
   *
   * @param iState
   * @param iTransition
   * @param iRobot
   */
  StateMachine(const State &iState,
               const Transition &iTransition,
               const std::shared_ptr<Robot> &iRobot)
    : state(iState), transition(iTransition), robot(iRobot) {
  }

  /**
   * @brief Goes through one step of the StateMachine.
   *
   * @return State
   */
  State step() {
    state = transition(*this);
    getState();
  }

  /**
   * @brief Get the State of the StateMachine.
   *
   * @return State
   */
  State getState() const {
    return state;
  }

  /**
   * @brief Run a user-defined transition.
   *
   * @param iTransition
   */
  void run(const Transition &iTransition) {
    transition = iTransition;
  }

  /**
   * @brief Get the pointer to the Robot used in the StateMachine (mostly here for use in
   * transitions).
   *
   * @return std::shared_ptr<Robot>
   */
  std::shared_ptr<Robot> getRobot() const {
    return robot;
  }

  protected:
  State state;
  Transition transition;
  std::shared_ptr<Robot> robot;
};

/**
 * @brief Provides easy-to-use type aliasing for transitions.
 *
 * @tparam State
 */
template <typename State> using Transition = std::function<State(StateMachine<State> &)>;
} // namespace bfb