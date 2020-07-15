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

#ifdef TESTING
DEFINE_TEST(recorderTest)
const RecordID testIDA{Recorder::giveID()};
const RecordID testIDB{Recorder::giveID()};
IS_EQUAL(testIDA, testIDB - 1);
END_TEST
#endif
} // namespace bfb