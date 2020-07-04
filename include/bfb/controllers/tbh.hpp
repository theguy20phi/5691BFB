#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/test.hpp"
#include "controller.hpp"
#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"

namespace bfb {
class Tbh : public Controller {
  public:
  Tbh(double iGain, std::unique_ptr<okapi::SettledUtil> iSettledChecker);
  void setReference(const double iReference) override;
  double getReference() const override;
  double step(const double state) override;
  double getOutput() const override;
  bool isSettled(const double state) override;
  void reset() override;

  private:
  void takeBackHalf(const int errorSign);

  private:
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
