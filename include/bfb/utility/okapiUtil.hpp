/**
 * @file okapiUtil.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief The okapiUtil file provides methods to better suit the rest of the bfb library.
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "okapi/api/control/util/settledUtil.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include <memory>

namespace bfb {
using namespace okapi::literals;
/**
 * @brief Eases the process of creating a SettledUtil.
 *
 * @param iatTargetError
 * @param iatTargetDerivative
 * @param iatTargetTime
 * @return std::unique_ptr<okapi::SettledUtil>
 */
std::unique_ptr<okapi::SettledUtil> createSettledUtil(double iatTargetError = 50,
                                                      double iatTargetDerivative = 5,
                                                      okapi::QTime iatTargetTime = 250_ms);


} // namespace bfb