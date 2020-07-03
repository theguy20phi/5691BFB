#pragma once

#include "test.hpp"
#include <cmath>

namespace bfb {
bool isAlmostEqual(const double a, const double b, const double thresh);
bool isAlmostZero(const double a, const double thresh);
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