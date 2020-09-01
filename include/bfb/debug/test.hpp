/**
 * @file test.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief The test file implements a very simple framework for testing.
 * This allows tests to be ran on the V5 brain, which is beneficial, as it doesn't require a complex
 * compilation nor as many mock implementations
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <iostream>

#define DECLARE_TEST(a) void a();

#define DEFINE_TEST(a) void a() {

#define END_TEST                                                                                   \
  std::cout << "Test " << __FUNCTION__ << " succeeded!" << std::endl;                              \
  }

#define IS_TRUE(a)                                                                                 \
  if (!a) {                                                                                        \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected true, was false.  See file "        \
              << __FILE__ << " line " << __LINE__ << "." << std::endl;                             \
    return;                                                                                        \
  }

#define IS_FALSE(a)                                                                                \
  if (a) {                                                                                         \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected false, was true.  See file "        \
              << __FILE__ << " line " << __LINE__ << "." << std::endl;                             \
    return;                                                                                        \
  }

#define IS_EQUAL(a, b)                                                                             \
  if (a != b) {                                                                                    \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected " << a << " was " << b              \
              << ". See file " << __FILE__ << " line " << __LINE__ << " for context."              \
              << std::endl;                                                                        \
    return;                                                                                        \
  }

namespace bfb {
/**
 * @brief Provided function to add user-defined tests to.
 *
 */
void runTests();
} // namespace bfb
