/**
 * The mathUtil file implements math related methods and functions that are of use in many files.
 *
 * @author Braden Pierce
 */
#pragma once

#include "test.hpp"
#include <cmath>

namespace bfb {
/**
 * Determines if two variables are equivalent given some threshold.
 *
 * @param a First value.
 * @param b Second value.
 * @param thresh The threshold.
 * @return If the values are almost equal.
 */
bool isAlmostEqual(const double a, const double b, const double thresh);

/**
 * Determines if a variable is almost zero given some threshold.
 *
 * @param a The value.
 * @param thresh The threshold.
 * @return If the value is almost zero.
 */
bool isAlmostZero(const double a, const double thresh);

/**
 * Determines the sign of a value.
 *
 * @param value The value.
 * @return Negative one if negative, positive one if positive, zero otherwise.
 */
template <class T> int sign(const T value) {
  if (value < 0)
    return -1;
  else if (value > 0)
    return 1;
  return 0;
}

#ifdef TESTING
DECLARE_TEST(isAlmostEqualTest)
DECLARE_TEST(signTest)
#endif
} // namespace bfb