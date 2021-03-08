#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/interpolate.h>

namespace gos {
namespace interpolate {

TEST(GosInterpolateTest, Linear) {
  double y1, y2, mu;
  double result;

  y1 = 1.0;
  y2 = 2.0;
  mu = 0.5;
  result = ::gos::interpolate::linear(y1, y2, mu);
  EXPECT_DOUBLE_EQ(1.5, mu);
}

} // namespace interpolate
} // namespace gos
