#ifndef GOSPP_INTERPOLATE_H_
#define GOSPP_INTERPOLATE_H_

#include <cmath>

namespace gos {
namespace interpolate {

template<typename T>
T linear(const T& y1, const T& y2, const T& mu) {
  return y1 * (T(1) - mu) + y2 * mu;
}

template<typename T>
T cosine(const T& y1, const T& y2, const T& mu) {
  T mu2 = (T(1) - cos(mu * M_PI)) / T(2);
  return y1 * (T(1) - mu2) + y2 * mu2;
}

} // namespace interpolate
} // namespace gos

#endif
