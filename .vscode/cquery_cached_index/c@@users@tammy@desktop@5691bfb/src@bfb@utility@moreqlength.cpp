#include "moreQLength.hpp"

namespace bfb {
#ifdef TESTING
DEFINE_TEST(moreQLengthTest)
using namespace bfb::literals;
okapi::QLength testTile = 2.5_tile;
okapi::QLength testBall = 2.5_element;
okapi::QLength testBotLength = 2.5_bot_length;
okapi::QLength testBotWidth = 2.5_bot_width;
IS_EQUAL(testTile.getValue(), (2.5_tile).getValue())
IS_EQUAL(testBall.getValue(), 2.5 * element.getValue())
IS_EQUAL(testBotLength.getValue(), 2.5 * testBotLength.getValue())
IS_EQUAL(testBotWidth.getValue(), 2.5 * testBotWidth.getValue())
END_TEST
#endif
} // namespace bfb