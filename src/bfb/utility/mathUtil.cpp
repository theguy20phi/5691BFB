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
} // namespace bfb