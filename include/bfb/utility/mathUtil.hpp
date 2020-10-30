/**
 * @file mathUtil.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief The mathUtil file implements math related methods and functions that are of use in many
 * files.
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once

#include "bfb/debug/test.hpp"
#include <cmath>

namespace bfb {
/**
 * @brief Determines if two variables are equivalent given some threshold.
 *
 * @param a
 * @param b
 * @param thresh
 * @return bool
 */
bool isAlmostEqual(double a, double b, double thresh);

/**
 * @brief Determines if a variable is almost zero given some threshold.
 *
 * @param a
 * @param thresh
 * @return bool
 */
bool isAlmostZero(double a, double thresh = 0.1);

/**
 * @brief Determines the sign of a value.
 *
 * @tparam T
 * @param value
 * @return int
 */
template <typename T> int sign(const T &value) {
  if (value < 0)
    return -1;
  else if (value > 0)
    return 1;
  return 0;
}

/**
 * @brief Takes an angle in degrees and outputs an angle in radians.
 *
 * @param angle
 * @return double
 */
constexpr double toRadians(double angle) {
  return angle * M_PI / 180.0;
}

/**
 * @brief Takes an angle in radians and outputs an angle in degrees.
 *
 * @param angle
 * @return double
 */
constexpr double toDegrees(double angle) {
  return angle * 180.0 / M_PI;
}

/**
 * @brief Takes an angle in radians and returns an angle in the form of (-PI, PI)
 *
 * @param angle
 * @return double
 */
double normalizeAngle(double angle);

#ifdef TESTING
DECLARE_TEST(isAlmostEqualTest)
DECLARE_TEST(signTest)
#endif
} // namespace bfb