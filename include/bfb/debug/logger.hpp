/**
 * @file logger.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * @brief
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <fstream>
#include <iostream>

namespace bfb {
/**
 * @brief Implements a logger for logging either to a file or the terminal.
 *
 */
class Logger final {
  public:
  /**
   * @brief Enables logging.
   * 
   */
  void enable();

  /**
   * @brief Disables logging.
   * 
   */
  void disable();

  /**
   * @brief Set the path to print to.
   * 
   * @param iPath 
   */
  void setPath(const std::string &iPath);

  /**
   * @brief Output the message.
   * 
   * @param message 
   */
  void operator<<(const std::string &message) const;

  private:
  bool disabled{true};
  std::string path{""};
};
} // namespace bfb