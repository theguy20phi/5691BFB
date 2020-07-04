#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/okapiUtil.hpp"
#include "bfb/utility/test.hpp"
#include "controller.hpp"

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
  double getReference() const override;
  double step(const double state) override;
  double getOutput() const override;
  bool isSettled(const double state) override;
  void reset() override;

  private:
  void updateI(const double error);
  double calculateD(const double state);

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