#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "controller.hpp"
#include "okapi/api/util/timeUtil.hpp"
#include <memory>


namespace bfb {
struct PidfConstants {
  double kP{};
  double kI{};
  double kD{};
  double f{};
};

class Pidf : public Controller {
  public:
  Pidf(const PidfConstants &iConstants, const okapi::TimeUtil &iTimeUtil);
  void setReference(double iReference) override;
  double step(double state) override;
  double getOutput() const override;
  bool isSettled(double state) override;
  void reset() override;

  private:
  static const double I_DECAY;
  const PidfConstants constants;
  std::unique_ptr<okapi::SettledUtil> settledChecker;
  double reference{0.0};
  double output{0.0};
  double previousState{0.0};
  double I{0.0};
};
} // namespace bfb