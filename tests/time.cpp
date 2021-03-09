#include <chrono>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/time.h>

namespace gos {
namespace time {

typedef ::std::chrono::high_resolution_clock clock;
typedef clock::duration duration;
typedef clock::time_point time;

const duration moment = duration();
TEST(GosTimeTest, NearestNeighbor) {
  time first, second, value;
  duration result;

  value = clock::now();

  first = value + ::std::chrono::minutes(10);
  second = value + ::std::chrono::minutes(20);
  result = ::gos::time::nearest::neighbor<time, duration>(first, second, value);
  EXPECT_GT(moment, result);

  first = value - ::std::chrono::minutes(10);
  second = value + ::std::chrono::minutes(25);
  result = ::gos::time::nearest::neighbor<time, duration>(first, second, value);
  EXPECT_GT(moment, result);

  first = value - ::std::chrono::minutes(15);
  second = value + ::std::chrono::minutes(10);
  result = ::gos::time::nearest::neighbor<time, duration>(first, second, value);
  EXPECT_LT(moment, result);

  first = value - ::std::chrono::minutes(25);
  second = value - ::std::chrono::minutes(10);
  result = ::gos::time::nearest::neighbor<time, duration>(first, second, value);
  EXPECT_LT(moment, result);
}

} // namespace time
} // namespace gos
