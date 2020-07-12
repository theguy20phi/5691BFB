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
#endif
}
} // namespace bfb