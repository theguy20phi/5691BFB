#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

namespace bfb {
using RecordID = int;

/**
 * @brief Provides a way to selectively record information.
 * 
 */
class Recorder {
  public:
  /**
   * @brief Set which IDs to record.
   *
   * @param iIDs
   */
  static void recordTheseIDs(const std::vector<RecordID> &iIDs);

  /**
   * @brief Gives a unique ID on request.
   *
   * @return RecordID
   */
  static RecordID giveID();

  /**
   * @brief Outputs the string to the terminal if the ID is found on the ID list.
   *
   * @param recording
   * @param ID
   */
  static void record(const std::string &recording, RecordID ID);

  private:
  static std::vector<RecordID> IDs;
  static int latestID;
};
} // namespace bfb