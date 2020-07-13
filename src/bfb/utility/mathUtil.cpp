#include "mathUtil.hpp"

namespace bfb {
bool isAlmostEqual(double a, double b, double thresh) {
  if (std::abs(a - b) <= thresh) {
    return true;
  }
  return false;
}

bool isAlmostZero(double a, double thresh) {
  return isAlmostEqual(a, 0.0, thresh);
}
#ifdef TESTING
DEFINE_TEST(isAlmostEqualTest)
IS_TRUE(isAlmostEqual(0.1, 0.12, 0.03))
IS_FALSE(isAlmostEqual(3.0, 3.4, 0.1))
END_TEST

DEFINE_TEST(signTest)
IS_EQUAL(sign(-1.5), -1)
IS_EQUAL(sign(1), 1)
IS_EQUAL(sign(0), 0)
END_TEST
#endif
} // namespace bfb