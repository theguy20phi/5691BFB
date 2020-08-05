/**
 * @file pidf.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/test.hpp"
#include "bfb/flow/wait.hpp"
#include "bfb/utility/mathUtil.hpp"
#include "bfb/utility/okapiUtil.hpp"
#include "controller.hpp"
#include "okapi/api/filter/emaFilter.hpp"

namespace bfb {
/**
 * @brief Pidf implements a basic PID+ff controller, with additions to prevent integral windup and
 * derivative kick, as well as determine if the controller is settled. Only calculates every >=10ms.
 *
 */
class Pidf final : public Controller {
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
  double calculate(double state) override;
  bool isDone(double state) override;
  void reset() override;

  /**
   * @brief Logger object for Pidf.
   *
   */
  static Logger pidfLog;

  private:
  /**
   * @brief Calculates the P term of the controller.
   *
   * @param error
   * @return double
   */
  double calculateP(double error);

  /**
   * @brief Calculates the I term of the controller.
   *
   * @param error
   * @return double
   */
  double calculateI(double error);

  /**
   * @brief Calculates the D term for a step of the controller.
   *
   * @param state
   */
  double calculateD(double state);

  private:
  static constexpr double I_DECAY{0.95};
  int previousSign{1};
  const PidfGains gains;
  std::unique_ptr<okapi::SettledUtil> settledChecker;
  std::uint32_t lastTime{0};
  okapi::EmaFilter dFilter{0.5};
  double I{0.0};
  double previousState{0.0};
};

#ifdef TESTING
DECLARE_TEST(pidfTest);
#endif
} // namespace bfb