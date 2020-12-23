/**
 * @file moreQLength.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief The moreQLength file expands upon the QLength file in okapi with more units.
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/debug/test.hpp"
#include "bfb/utility/mathUtil.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"

namespace bfb {
enum class Color { Blue, Red };

inline namespace literals {
constexpr okapi::QLength operator""_tile(long double x) {
  return x * 24.0 * okapi::inch;
}
constexpr okapi::QLength operator""_element(long double x) {
  return x * 6.3 * okapi::inch;
}
constexpr okapi::QLength operator""_bot_width(long double x) {
  return x * 17.5 * okapi::inch;
}
constexpr okapi::QLength operator""_bot_length(long double x) {
  return x * 17.5 * okapi::inch;
}
} // namespace literals
} // namespace bfb
