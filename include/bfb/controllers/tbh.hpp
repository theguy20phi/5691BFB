/**
 * @file tbh.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/test.hpp"
#include "bfb/utility/mathUtil.hpp"
#include "controller.hpp"
#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"
#include <assert.h>

namespace bfb {
/**
 * @brief Tbh implements a Take-Back-Half controller, essentially a modified integrator, with the
 * addition of a method to check if the controller is settled.
 *
 */
class Tbh final : public Controller {
  public:
  /**
   * @brief Constructs a Tbh object.
   *
   * @warning Asserted that gain >= 0.0.
   * @param iGain
   * @param iSettledChecker
   */
  Tbh(double iGain, std::unique_ptr<okapi::SettledUtil> iSettledChecker);

  double step(double state) override;
  bool isDone(double state) override;
  void reset() override;

  private:
  /**
   * @brief Does the "Take-Back-Half" part of the algorithm.
   *
   * @param errorSign
   */
  void takeBackHalf(int errorSign);

  const double gain;
  std::unique_ptr<okapi::SettledUtil> settledChecker;
  double tbh{0.0};
  double previousErrorSign{0};
};

#ifdef TESTING
DECLARE_TEST(tbhTest);
#endif
} // namespace bfb
