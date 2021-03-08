#ifndef GOSPP_NOISE_H_
#define GOSPP_NOISE_H_

#include <cstdlib>

#define GOS_NOISE_DEFAULT_SEED 1337

// Hashing
#define GOS_NOISE_X_PRIME 1619
#define GOS_NOISE_Y_PRIME 31337

namespace gos {
namespace noise {

template<typename T = double, typename U = int>
T white(const U& seed, const U& x, const U& y) {
  U n;
  long l;
  n = seed;
  n ^= GOS_NOISE_X_PRIME * x;
  n ^= GOS_NOISE_Y_PRIME * y;
  l = n * n * n * 60493;
  return static_cast<T>(l) / 2147483648.0;
}

} // namespace noise
} // namespace gos

#endif
