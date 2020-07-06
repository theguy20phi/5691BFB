/**
 * The okapiUtil file provides methods to better suit the rest of the bfb library.
 *
 * @author Braden Pierce
 */
#pragma once

#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"
#include <memory>

namespace bfb {
using namespace okapi::literals;
/**
 * Eases the process of creating a SettledUtil.
 *
 * @param iatTargetError The target error for SettledUtil.
 * @param iatTargetDerivative The target derivative of error for the SettledUtil.
 * @param iatTargetTime The target time the at the target derivative for the SettledUtil.
 * @return A unique pointer for a SettledUtil.
 */
std::unique_ptr<okapi::SettledUtil> createSettledUtil(double iatTargetError = 50,
                                                      double iatTargetDerivative = 5,
                                                      okapi::QTime iatTargetTime = 250_ms);
} // namespace bfb