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
#endif
}
} // namespace bfb