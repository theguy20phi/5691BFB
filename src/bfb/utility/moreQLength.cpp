#include "moreQLength.hpp"

namespace bfb {
#ifdef TESTING
DEFINE_TEST(moreQLengthTest)
using namespace bfb::literals;
okapi::QLength testTile = 1.0_tile;
okapi::QLength testBall = 1.0_ball;
IS_EQUAL(testTile.getValue(), 0.6096000000000000307)
IS_EQUAL(testTile.getValue(), 0.1600200000000000233)
END_TEST
#endif
} // namespace bfb