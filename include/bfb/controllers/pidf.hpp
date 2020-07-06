/**
 * Pidf implements a basic PID+ff controller, with additions to prevent integral windup and
 * derivative kick, as well as determine if the controller is settled.
 *
 * @author Braden Pierce
 */
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

  /**
   * Constructs a Pidf object.
   *
   * @param gains The gains that will be used.
   * @param iSettledChecker The SettledUtil that will be used (use createSettledUtil).
   */
  Pidf(const PidfGains &gains, std::unique_ptr<okapi::SettledUtil> iSettledChecker);

  void setReference(const double iReference) override;
  double getReference() const override;
  double step(const double state) override;
  double getOutput() const override;
  bool isSettled(const double state) override;
  void reset() override;

  private:
  /**
   * Updates the I term of the controller.
   *
   * @param error The error this step.
   */
  void updateI(const double error);

  /**
   * Calculates the D term for a step of the controller.
   *
   * @param state The state this step.
   */
  double calculateD(const double state);

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