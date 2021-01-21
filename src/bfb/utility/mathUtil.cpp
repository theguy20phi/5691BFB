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

double normalizeAngle(double angle) {
  return angle - 2.0 * M_PI * std::floor((angle + M_PI) / (2 * M_PI));
}
} // namespace bfb