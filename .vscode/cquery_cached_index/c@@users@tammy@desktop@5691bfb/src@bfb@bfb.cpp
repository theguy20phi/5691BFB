#include "bfb.hpp"

namespace bfb {
void runTests() {
#ifdef TESTING
  pidfTest();
  isAlmostEqualTest();
  signTest();
  tbhTest();
  issueTest();
  waitUntilTest();
  waitUntilWithTimeoutTest();
  bangBangTest();
  initializeCrossOdometryTest();
  std::cout << "Completed tests!" << std::endl;
#endif
}
} // namespace bfb