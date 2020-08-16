/**
 * @file logger.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "bfb/utility/key.hpp"
#include <fstream>
#include <iostream>

namespace bfb {
/**
 * @brief Implements a logger for logging either to a file or the terminal.
 *
 * @tparam Client
 */
template <typename Client> class Logger final {
  public:
  /**
   * @brief Enables logging.
   *
   */
  void enable() {
    disabled = false;
  }

  /**
   * @brief Disables logging.
   *
   */
  void disable() {
    disabled = true;
  }

  /**
   * @brief Set the path to print to.
   *
   * @param iPath
   */
  void setPath(const std::string &iPath) {
    path = iPath;
  }

  /**
   * @brief Output the message.
   *
   * @param message
   */
  void log(const std::string &message, const Key<Client> &key) const {
    if (disabled)
      return;
    std::cout << message << std::endl;
    if (path == "")
      return;
    std::ofstream file;
    file.open(path, std::ios::app);
    file << message << std::endl;
    file.close();
  }

  private:
  bool disabled{true};
  std::string path{""};
};
} // namespace bfb