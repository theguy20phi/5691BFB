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
  taskTest();
  std::cout << "Completed tests!" << std::endl;
#endif
}
} // namespace bfb