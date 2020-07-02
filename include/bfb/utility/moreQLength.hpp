#pragma once

#include "okapi/api/units/QLength.hpp"
#include "test.hpp"

namespace bfb {

constexpr okapi::QLength tile = 2 * okapi::foot;
constexpr okapi::QLength ball = 6.3 * okapi::inch;

inline namespace literals {
constexpr okapi::QLength operator"" _tile(long double x) {
  return static_cast<double>(x) * tile;
}
constexpr okapi::QLength operator"" _ball(long double x) {
  return static_cast<double>(x) * ball;
}
} // namespace literals
} // namespace bfb

#ifdef TESTING
DECLARE_TEST(moreQLengthTest)
#endif
