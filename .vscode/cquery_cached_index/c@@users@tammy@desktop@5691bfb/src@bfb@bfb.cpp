#include "bfb.hpp"

namespace bfb {
void runTests() {
#ifdef TESTING
  moreQLengthTest();
  pidfTest();
  isAlmostEqualTest();
  signTest();
  tbhTest();
  issueTest();
  waitUntilTest();
#endif
}
} // namespace bfb