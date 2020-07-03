#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/test.hpp"
#include "controller.hpp"
#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"
#include <memory>

namespace bfb {
class Pidf : public Controller {
  public:
  struct PidfGains {
    double kP{};
    double kI{};
    double kD{};
    double f{};
  };
  Pidf(const PidfGains &gains, std::unique_ptr<okapi::SettledUtil> iSettledChecker);
  void setReference(const double iReference) override;
  double step(const double state) override;
  double getOutput() const override;
  bool isSettled(const double state) override;
  void reset() override;

  private:
  static constexpr double I_DECAY{0.95};
  const PidfGains gains;
  std::unique_ptr<okapi::SettledUtil> settledChecker;
  double output{0.0};
  double reference{0.0};
  double I{0.0};
  double previousState{0.0};
};

#ifdef TESTING
DECLARE_TEST(pidfTest)
#endif
} // namespace bfb