#pragma once

#include "okapi/api/units/QLength.hpp"
#include "test.hpp"

namespace bfb {

constexpr okapi::QLength tile = 2 * okapi::foot;
constexpr okapi::QLength element = 6.3 * okapi::inch;
constexpr okapi::QLength bot_width = 18.0 * okapi::inch;
constexpr okapi::QLength bot_length = 18.0 * okapi::inch;
inline namespace literals {
constexpr okapi::QLength operator"" _tile(long double x) {
  return static_cast<double>(x) * tile;
}
constexpr okapi::QLength operator"" _element(long double x) {
  return static_cast<double>(x) * element;
}
constexpr okapi::QLength operator"" _bot_width(long double x) {
  return static_cast<double>(x) * bot_width;
}
constexpr okapi::QLength operator"" _bot_length(long double x) {
  return static_cast<double>(x) * bot_length;
}
} // namespace literals

#ifdef TESTING
DECLARE_TEST(moreQLengthTest)
#endif
} // namespace bfb
