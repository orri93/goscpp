#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/scale.h>

namespace gos {
namespace test {
namespace scale {

TEST(GosScaleTest, Value) {
  ::gos::scale<> scale;
  double s;

  scale.setdomain(::gos::range::make_d1(1.0, 2.0));
  scale.setrange(::gos::range::make_d1(10.0, 20.0));
  s = scale.value(0.0);
  EXPECT_DOUBLE_EQ(0.0, s);
  s = scale.value(1.0);
  EXPECT_DOUBLE_EQ(10.0, s);
  s = scale.value(1.5);
  EXPECT_DOUBLE_EQ(15.0, s);
  s = scale.value(2.0);
  EXPECT_DOUBLE_EQ(20.0, s);
  s = scale.value(3.0);
  EXPECT_DOUBLE_EQ(30.0, s);

  scale.setdomain(::gos::range::make_d1(1.0, 2.0));
  scale.setrange(::gos::range::make_d1(20.0, 10.0));
  s = scale.value(1.0);
  EXPECT_DOUBLE_EQ(20.0, s);
  s = scale.value(1.5);
  EXPECT_DOUBLE_EQ(15.0, s);
  s = scale.value(2.0);
  EXPECT_DOUBLE_EQ(10.0, s);
}

TEST(GosScaleTest, Reverse) {
  ::gos::scale<> scale;
  double r;

  scale = ::gos::make_scale(1.0, 2.0, 10.0, 20.0);
  r = scale.reverse(0.0);
  EXPECT_DOUBLE_EQ(0.0, r);
  r = scale.reverse(10.0);
  EXPECT_DOUBLE_EQ(1.0, r);
  r = scale.reverse(15.0);
  EXPECT_DOUBLE_EQ(1.5, r);
  r = scale.reverse(20.0);
  EXPECT_DOUBLE_EQ(2.0, r);
  r = scale.reverse(30.0);
  EXPECT_DOUBLE_EQ(3.0, r);

  scale = ::gos::make_scale(1.0, 2.0, 20.0, 10.0);
  r = scale.reverse(20.0);
  EXPECT_DOUBLE_EQ(1.0, r);
  r = scale.reverse(15.0);
  EXPECT_DOUBLE_EQ(1.5, r);
  r = scale.reverse(10.0);
  EXPECT_DOUBLE_EQ(2.0, r);
}

} // namespace scale
} // namespace test
} // namespace gos
