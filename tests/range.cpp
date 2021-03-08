#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/scale.h>

namespace gos {
namespace range {

TEST(GosRangeTest, Difference) {
  ::gos::range::d1<> range;
  double result;

  range = ::gos::range::make_d1(10.0, 30.0);
  result = range.difference();
  EXPECT_DOUBLE_EQ(20.0, result);
}

} // namespace range
} // namespace gos
