/**
 * @file pidf.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/okapiUtil.hpp"
#include "bfb/utility/test.hpp"
#include "controller.hpp"

namespace bfb {
/**
 * @brief Pidf implements a basic PID+ff controller, with additions to prevent integral windup and
 * derivative kick, as well as determine if the controller is settled.
 *
 */
class Pidf : public Controller {
  public:
  /**
   * @brief Provides a data structure for the Pidf's constants.
   *
   */
  struct PidfGains {
    double kP{};
    double kI{};
    double kD{};
    double f{};
  };

  /**
   * @brief Constructs a Pidf object.
   *
   * @param gains
   * @param iSettledChecker
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
   * @brief Updates the I term of the controller.
   *
   * @param error
   */
  void updateI(const double error);

  /**
   * @brief Calculates the D term for a step of the controller.
   *
   * @param state
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