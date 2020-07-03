#include <iostream>

#define TESTING

#define DECLARE_TEST(a) void a();

#define DEFINE_TEST(a) void a() {

#define END_TEST                                                                                   \
  std::cout << "Test " << __FUNCTION__ << " succeeded!" << std::endl;                              \
  }

#define IS_TRUE(a)                                                                                 \
  if (!a) {                                                                                        \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected true, was false.  See file "        \
              << __FILE__ << " line " << __LINE__ << "." << std::endl;                             \
    return;                                                                                        \
  }

#define IS_FALSE(a)                                                                                \
  if (a) {                                                                                         \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected false, was true.  See file "        \
              << __FILE__ << " line " << __LINE__ << "." << std::endl;                             \
    return;                                                                                        \
  }

#define IS_EQUAL(a, b)                                                                             \
  if (a != b) {                                                                                    \
    std::cout << "Test " << __FUNCTION__ << " failed. Expected " << a << " was " << b              \
              << ". See file " << __FILE__ << " line " << __LINE__ << " for context."              \
              << std::endl;                                                                        \
    return;                                                                                        \
  }

namespace bfb {
void runTests();
}
