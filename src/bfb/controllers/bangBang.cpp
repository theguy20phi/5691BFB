#include "bangBang.hpp"

namespace bfb {
BangBang::BangBang(const BangBangMap &iMap, double iMax) : map(iMap), max(iMax) {
  // should be sorted from greatest to least error
  std::sort(map.begin(), map.end(), [](const BangBangPair &a, const BangBangPair &b) {
    return a.error > b.error;
  });
  bangBangLog.log("Bang-Bang created.", {});
}

double BangBang::calculate(double state) {
  double error{fabs(state - reference)};
  double temp{max};
  for (BangBangPair p : map)
    if (error < p.error)
      temp = p.output;
  output = sign(error) * temp;
  return output;
}

bool BangBang::isDone(double state) {
  if (state - reference < map.back().error)
    return true;
  return false;
}

void BangBang::reset() {
  output = 0.0;
  reference = 0.0;
}

Logger<BangBang> BangBang::bangBangLog{};
} // namespace bfb