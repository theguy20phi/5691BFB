#include "recorder.hpp"

namespace bfb {
void Recorder::recordTheseIDs(const std::vector<RecordID> &iIDs) {
  IDs = iIDs;
}

RecordID Recorder::giveID() {
  latestID++;
  return latestID;
}

void Recorder::record(const std::string &recording, RecordID ID) {
  if (std::count(IDs.begin(), IDs.end(), ID))
    std::cout << recording << std::endl;
}

std::vector<RecordID> Recorder::IDs{};
int Recorder::latestID{0};
} // namespace bfb