#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/screen.h>

namespace gos {
namespace test {
namespace screen {

TEST(GosScreenTest, Index) {
  ::gos::screen<> screen;
  size_t i;

  screen = ::gos::make_screen(600, 400);
  i = screen.index(0, 0);
  EXPECT_EQ(0, i);
  i = screen.index(1, 0);
  EXPECT_EQ(1, i);
  i = screen.index(2, 0);
  EXPECT_EQ(2, i);
  i = screen.index(599, 0);
  EXPECT_EQ(599, i);
  i = screen.index(0, 1);
  EXPECT_EQ(600, i);
  i = screen.index(0, 2);
  EXPECT_EQ(1200, i);
  i = screen.index(1, 2);
  EXPECT_EQ(1201, i);
  i = screen.index(11, 2);
  EXPECT_EQ(1211, i);
}

} // namespace screen
} // namespace test
} // namespace gos
