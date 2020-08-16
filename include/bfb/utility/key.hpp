/**
 * @file attorney.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

namespace bfb {
/**
 * @brief Makes using the Passkey pattern much easier for safer friendship.
 *
 * @tparam Client
 */
template <typename Client> class Key {
  friend Client;
  Key() {
  }
};
} // namespace bfb