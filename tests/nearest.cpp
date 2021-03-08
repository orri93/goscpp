#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/nearest.h>

namespace gos {
namespace nearest {

TEST(GosNearestTest, Neighbor) {
  double first, second, value;
  double result;

  first = 10.0;
  second = 20.0;

  value = 5.0;
  result = neighbor(first, second, value);
  EXPECT_GT(0.0, result);

  value = 12.0;
  result = neighbor(first, second, value);
  EXPECT_GT(0.0, result);

  value = 18.0;
  result = neighbor(first, second, value);
  EXPECT_LT(0.0, result);

  value = 25.0;
  result = neighbor(first, second, value);
  EXPECT_LT(0.0, result);
}

TEST(GosNearestTest, TimeNeighbor) {
  time_t first, second, value;
  time_t result;

  first = 10;
  second = 20;

  value = 5;
  result = neighbor(first, second, value);
  EXPECT_GT(0, result);

  value = 12;
  result = neighbor(first, second, value);
  EXPECT_GT(0, result);

  value = 18;
  result = neighbor(first, second, value);
  EXPECT_LT(0, result);

  value = 25;
  result = neighbor(first, second, value);
  EXPECT_LT(0, result);
}

}
}
