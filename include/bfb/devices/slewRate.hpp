/**
 * @file slewRate.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once

#include <algorithm>

namespace bfb {
/**
 * @brief Implements a slew rate to manipulate maximum acceleration.
 *
 * @tparam Type
 */
template <typename Type> class SlewRate final {
  public:
  /**
   * @brief Construct a new Slew Rate object
   *
   * @param iMaxChange
   */
  SlewRate(Type iMaxChange) : maxChange(iMaxChange) {
  }

  /**
   * @brief "Slews" the value given.
   *
   * @param desired
   * @return Type
   */
  Type slew(Type desired) {
    value += std::clamp(desired - value, -maxChange, maxChange);
    return value;
  }

  /**
   * @brief Get the value of the slew rate.
   *
   * @return Type
   */
  Type getValue() const {
    return value;
  }

  private:
  const Type maxChange;
  Type value{0};
};
} // namespace bfb