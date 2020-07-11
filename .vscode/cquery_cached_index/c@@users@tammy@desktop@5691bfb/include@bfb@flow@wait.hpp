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
#include "bfb/utility/test.hpp"
#include <functional>

namespace bfb {
constexpr int vex_delay{10};

/**
 * @brief Provide a condition like:
 * waitUntil(somethingIsDone);
 * or
 * waitUntil([object]() -> bool { return object->isDone(); });
 * It will wait in vex_delay increments until the condition is achieved.
 * Lambdas can be initialized else where: auto condition = [<any locals go here>](){ <stuff> }
 * You can also place time exits in the function. 
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
DECLARE_TEST(waitUntilTest)
#endif
} // namespace bfb