#pragma once

#include "okapi/api/control/util/SettledUtil.hpp"
#include "okapi/impl/util/timer.hpp"
#include <memory>

namespace bfb {
using namespace okapi::literals;
std::unique_ptr<okapi::SettledUtil> createSettledUtil(double iatTargetError = 50,
                                                      double iatTargetDerivative = 5,
                                                      okapi::QTime iatTargetTime = 250_ms);
} // namespace bfb