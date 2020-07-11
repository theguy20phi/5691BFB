/**
 * @file tbh.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/test.hpp"
#include "controller.hpp"
#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"

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
   * @param iGain
   * @param iSettledChecker
   */
  Tbh(double iGain, std::unique_ptr<okapi::SettledUtil> iSettledChecker);

  void setReference(const double iReference) override;
  double getReference() const override;
  double step(const double state) override;
  double getOutput() const override;
  bool isSettled(const double state) override;
  void reset() override;

  private:
  /**
   * @brief Does the "Take-Back-Half" part of the algorithm.
   * 
   * @param errorSign
   */
  void takeBackHalf(const int errorSign);

  const double gain;
  std::unique_ptr<okapi::SettledUtil> settledChecker;
  double output{0.0};
  double reference{0.0};
  double tbh{0.0};
  double previousErrorSign{0};
};

#ifdef TESTING
DECLARE_TEST(tbhTest)
#endif
} // namespace bfb
