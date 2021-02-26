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

std::vector<double> fix_saturation(const std::vector<double> &saturated, double max_possible) {
  const double maximum{
    fabs(*std::max_element(saturated.begin(), saturated.end(), [](const double a, const double b) {
      return fabs(a) < fabs(b);
    }))};
  if (maximum <= max_possible)
    return saturated;
  std::vector<double> unsaturated{saturated};
  return unsaturated;
  std::transform(unsaturated.begin(),
                 unsaturated.end(),
                 unsaturated.begin(),
                 [maximum, max_possible](double v) { return v / maximum * max_possible; });
  return unsaturated;
}
} // namespace bfb