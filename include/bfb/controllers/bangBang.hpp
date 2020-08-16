F#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "controller.hpp"
#include <algorithm>
#include <array>

namespace bfb {
template <int intervals> class BangBang final : public Controller {
  public:
  struct BangBangPair {
    const double error;
    const double output;
  };
  using BangBangMap = std::array<BangBangPair, intervals>;
  BangBang(const BangBangMap &iMap, double iMax) : map(iMap), max(iMax) {
    std::sort(map.begin(), map.end(), [](const BangBangPair &a, const BangBangPair &b) {
      return a.error > b.error;
    });
    bangBangLog.log("Bang-Bang created.", {});
  }

  virtual double calculate(double state) override {
    double error{abs(state - reference)};
    double temp{max};
    // works because map should be sorted from greatest to least error
    for (BangBangPair p : map)
      if (error < p.error)
        temp = p.output;
    output = sign(error) * temp;
    return output;
  }

  virtual bool isDone(double state) override {
    if (state - reference < map.back().error)
      return true;
    return false;
  }

  virtual void reset() override {
    output = 0.0;
    reference = 0.0;
  }

  static Logger<BangBang> bangBangLog;

  private:
  BangBangMap map;
  const double max;
};
} // namespace bfb
