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
#include "okapi\api\filter\emaFilter.hpp"
#include <assert.h>

namespace bfb {
/**
 * @brief Pidf implements a basic PID+ff controller, with additions to prevent integral windup and
 * derivative kick, as well as determine if the controller is settled.
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
   * @warning Asserted that alls gains are >= 0.0.
   * @param gains
   * @param iSettledChecker
   */
  Pidf(const PidfGains &gains, std::unique_ptr<okapi::SettledUtil> iSettledChecker);

  double step(const double state) override;
  bool isDone(const double state) override;
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
  okapi::EmaFilter dFilter{0.5};
  double I{0.0};
  double previousState{0.0};
};

#ifdef TESTING
DECLARE_TEST(pidfTest)
#endif
} // namespace bfb