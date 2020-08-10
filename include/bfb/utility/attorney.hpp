/**
 * @file attorney.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

namespace bfb {
/**
 * @brief Makes using the Client-Attorney pattern much easier for safer friendship.
 *
 * @tparam Client
 */
template <typename Client> class Attorney {
  friend Client;
  Attorney() {
  }
};
} // namespace bfb