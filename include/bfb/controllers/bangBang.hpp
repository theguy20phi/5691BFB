/**
 * @file bangBang.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/test.hpp"
#include "bfb/utility/mathUtil.hpp"
#include "controller.hpp"
#include <algorithm>
#include <vector>

namespace bfb {
/**
 * @brief Implements a simple Bang-Bang controller.
 *
 * @tparam intervals
 */
class BangBang final : public Controller {
  public:
  struct BangBangPair {
    double error;
    double output;
  };
  using BangBangMap = std::vector<BangBangPair>;

  /**
   * @brief Construct a new BangBang object.
   *
   * @param iMap
   * @param iMax
   */
  BangBang(const BangBangMap &iMap, double iMax);

  double calculate(double state) override;

  bool isDone(double state) override;

  void reset() override;
  /**
   * @brief Logger object for BangBang.
   *
   */
  static Logger<BangBang> bangBangLog;

  private:
  BangBangMap map;
  const double max;
};

#ifdef TESTING
DECLARE_TEST(bangBangTest);
#endif
} // namespace bfb
