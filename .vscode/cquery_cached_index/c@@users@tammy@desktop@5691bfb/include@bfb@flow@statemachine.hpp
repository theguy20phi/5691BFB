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
 * @brief StateMachine implements a queue-based finite state machine, similar to a stack-based state
 * machine. States are enqueued, and when a state completes its behaviour, dequeued. A default state
 * should be provided. A StateMachine object can be limited to a certain type of state, via
 * templating. If something else needs to see the state of the machine, it should probably be a part
 * of the machine.
 *
 * @tparam StateType
 */
template <typename StateType> class StateMachine {
  public:
  /**
   * @brief Construct a new StateMachine object.
   *
   * @param iRobot
   * @param iDefaultState
   */
  StateMachine(const std::shared_ptr<Robot> &iRobot, const StateType &iDefaultState)
    : robot(iRobot), defaultState(iDefaultState) {
    enqueue(defaultState);
  }

  /**
   * @brief Goes through one step of the StateMachine.
   *
   */
  void step() {
    if (stateQueue.front()->step(robot))
      dequeue();
  }

  /**
   * @brief Determines if the StateMachine has completed its queue, excluding the default state.
   *
   * @return bool
   */
  bool isDone() const {
    // if size() = 0, !size() = 1 = true
    return !size();
  }

  /**
   * @brief Enqueues another state to be done.
   *
   * @param newState
   */
  void enqueue(const StateType &newState) {
    stateQueue.push(newState);
  }

  /**
   * @brief Removes all states from the queue.
   *
   */
  void dequeueAll() {
    //+1 accounts for the default state
    dequeue(size() + 1);
  }

  /**
   * @brief Removes n states from the queue.
   *
   * @param n
   */
  void dequeue(int n) {
    for (std::size_t i = 0; i < n; ++i)
      dequeue();
  }

  /**
   * @brief Removes a single state from the queue.
   *
   */
  void dequeue() {
    if (isDone())
      stateQueue.push(defaultState);
    stateQueue.pop();
  }

  /**
   * @brief Gets the size of the queue.
   *
   * @return std::size_t
   */
  std::size_t size() const {
    //-1 accounts for the default state, which most aren't interested in
    return stateQueue.size() - 1;
  }

  /**
   * @brief Gets the state in string form. SHOULD ONLY BE USED FOR DEBUGGING.
   *
   * @return std::string
   */
  std::string toString() const {
    return typeid(*stateQueue.front()).name();
  }

  private:
  std::shared_ptr<Robot> robot;
  const StateType defaultState;
  std::queue<StateType> stateQueue;
};
} // namespace bfb