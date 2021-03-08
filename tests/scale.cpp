#include <ctime>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/scale.h>

namespace gos {
namespace test {
namespace scale {

TEST(GosScaleTest, Value) {
  ::gos::scale<> scale;
  double s;
  int i;

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

  ::gos::scale<double, int> s2 =
    ::gos::make_scale<double, int>(1.0, 5.0, 100, 200);
  i = s2.value(2.0);
  EXPECT_EQ(125, i);
  i = s2.value(3.0);
  EXPECT_EQ(150, i);
  i = s2.value(4.0);
  EXPECT_EQ(175, i);

  ::gos::scale<time_t, int> s3 =
    ::gos::make_scale<time_t, int>(640000, 660000, 100, 400);
  i = s3.value(600000);
  EXPECT_EQ(-500, i);
  i = s3.value(620000);
  EXPECT_EQ(-200, i);
  i = s3.value(640000);
  EXPECT_EQ(100, i);
  i = s3.value(650000);
  EXPECT_EQ(250, i);
  i = s3.value(660000);
  EXPECT_EQ(400, i);
  i = s3.value(680000);
  EXPECT_EQ(700, i);
}

TEST(GosScaleTest, Reverse) {
  ::gos::scale<> scale;
  double r, f;
  time_t t;

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

  ::gos::scale<double, int> s2 =
    ::gos::make_scale<double, int>(1.0, 5.0, 100, 200);
  f = s2.reverse(125);
  EXPECT_DOUBLE_EQ(2.0, f);
  f = s2.reverse(150);
  EXPECT_DOUBLE_EQ(3.0, f);
  f = s2.reverse(175);
  EXPECT_DOUBLE_EQ(4.0, f);

  ::gos::scale<time_t, int> s3 =
    ::gos::make_scale<time_t, int>(640000, 660000, 100, 400);
  t = s3.reverse(-500);
  EXPECT_EQ(600000, t);
  t = s3.reverse(-200);
  EXPECT_EQ(620000, t);
  t = s3.reverse(100);
  EXPECT_EQ(640000, t);
  t = s3.reverse(250);
  EXPECT_EQ(650000, t);
  t = s3.reverse(400);
  EXPECT_EQ(660000, t);
  t = s3.reverse(700);
  EXPECT_EQ(680000, t);
}

} // namespace scale
} // namespace test
} // namespace gos
