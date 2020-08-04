/**
 * @file wait.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "api.h"
#include "bfb/debug/test.hpp"
#include <functional>

namespace bfb {
constexpr int generalDelay{10};

/**
 * @brief Provide a condition like:
 * waitUntil(somethingIsDone, 1000);
 * or
 * waitUntil([object]() -> bool { return object->isDone(); });
 * It will wait in vex_delay increments until the condition is achieved.
 * Will timeout, see overload without the maxDelay argument if that isn't desired.
 *
 * @param condition
 * @param maxDelay
 */
void waitUntil(const std::function<bool()> &condition, const int maxDelay);

/**
 * @brief Provide a condition like:
 * @code
 * waitUntil(somethingIsDone);
 * @endcode
 * or
 * @code
 * waitUntil([object]() -> bool { return object->isDone(); });
 * @endcode
 * It will wait in vex_delay increments until the condition is achieved.
 * Will not timeout, see overload with maxDelay argument.
 *
 * @param condition
 */
void waitUntil(const std::function<bool()> &condition);

/**
 * @brief Makes pros::Task::delay_until a bit easier to use, while still being useful for periodic
 * tasks that benefit from a more consistent delay.
 *
 * @param ms
 */
void wait(const int time);

#ifdef TESTING
DECLARE_TEST(waitUntilWithTimeoutTest)
DECLARE_TEST(waitUntilTest)
#endif
} // namespace bfb