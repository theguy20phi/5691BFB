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

namespace bfb {
inline namespace literals {
constexpr double operator""_rad(long double x) {
  return x;
}
constexpr double operator""_deg(long double x) {
  return toRadians(x);
}
constexpr double operator""_in(long double x) {
  return x;
}
constexpr double operator""_ft(long double x) {
  return x * 12.0;
}
constexpr double operator""_tile(long double x) {
  return x * 24.0;
}
constexpr double operator""_element(long double x) {
  return x * 6.3;
}
constexpr double operator""_bot_width(long double x) {
  return x * 17.5;
}
constexpr double operator""_bot_length(long double x) {
  return x * 17.5;
}
} // namespace literals
} // namespace bfb
