/**
 * @file stateMachine.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "task.hpp"
#include <iostream>
#include <type_traits>
#include <variant>

namespace bfb {
/**
 * @brief A template for StateMachines. The state is represented by a variant of structs that
 * represent specific states. The subclasses must provide behavior for each possible specific state
 * the state variant could be with a function for each state: behavior(const State &state) {...}.
 *
 * This implementation avoids lengthy switch statements, verbose expansion using polymorphic states,
 *
 * @code
 * namespace State {
 *  namespace Test { // probably want namespaces
 *    struct ON{int a}; // states can be paramaterized
 *    struct OFF{int b};
 *    using TestStates = std::variant<ON, OFF>; // probably want a type alias
 *  }
 * }
 * class TestMachine final : public StateMachine<TestMachine, TestStates> {
 *  public:
 *  // your state machine can have a unique constructor, or just call the StateMachine constructor
 *  TestMachine(const ValidStates &iState, <other parameters>) {...}
 *  // define all possible behavior or face dreaded C++ template errors
 *  void behavior(const State::Test::ON &on) {...}
 *  void behavior(const State::Test::OFF &off) {...}
 *
 *  private:
 *  void onHelper() {...} // Subclassed state machines can provide helpers for behaviors
 *
 *  private:
 *  Data data; // Subclassed statemachines can store data for use in behaviors
 * };
 * @endcode
 *
 * @tparam Concrete (the subclass)
 * @tparam ValidStates (variant of state structs)
 * @tparam TASK_PRIORITY_DEFAULT
 */
template <class Concrete, typename ValidStates> class StateMachine : public Task {
  public:
  /**
   * @brief Construct a new State Machine object
   *
   * @param iState
   */
  StateMachine(const ValidStates &iState, int iPriority = TASK_PRIORITY_DEFAULT)
    : state(iState), Task(iPriority) {
    stateMachineLog.log("StateMachine created.", {});
  }

  /**
   * @brief Overloads bfb::Task::step, uses a visitor to run the overloaded behavior for the current
   * state.
   *
   */
  virtual void step() final {
    std::visit([this](const auto &s) { static_cast<Concrete *>(this)->behavior(s); }, state);
    update();
  }

  /**
   * @brief Does various updates for the StateMachine each step.
   *
   */
  virtual void update() {
  }

  /**
   * @brief Set the State object
   *
   * @param iState
   */
  virtual void setState(const ValidStates &iState) {
    state = iState;
  }

  /**
   * @brief Get the State object
   *
   * @return ValidStates
   */
  virtual ValidStates getState() const final {
    return state;
  }

  /**
   * @brief Determines if two states are equal (does not take parameters into account).
   *
   * @param iState
   * @return bool
   */
  virtual bool operator==(const ValidStates &iState) const final {
    return state.index() == iState.index();
  }

  /**
   * @brief Determines if two states are not equal (does not take parameters into account).
   *
   * @param iState
   * @return bool
   */
  virtual bool operator!=(const ValidStates &iState) const final {
    return state.index() != iState.index();
  }

  /**
   * @brief Logger object for StateMachine.
   *
   */
  Logger<StateMachine<Concrete, ValidStates>> stateMachineLog{};

  protected:
  virtual void setStateInternally(const ValidStates &iState) {
    state = iState;
    step();
  }
  ValidStates state;
};
} // namespace bfb