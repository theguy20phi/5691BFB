#include "bangBang.hpp"

namespace bfb {
template <int intervals> Logger<BangBang<intervals>> BangBang<intervals>::bangBangLog;

DEFINE_TEST(bangBangTest)
BangBang<3> testBangBang{
  std::array<BangBang<3>::BangBangPair, 3>{{{30.0, 100.0}, {60.0, 200.0}, {90.0, 300.0}}},
  400};
IS_EQUAL(100, testBangBang.calculate(20));
IS_EQUAL(200, testBangBang.calculate(40));
END_TEST
} // namespace bfb