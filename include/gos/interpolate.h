#ifndef GOSPP_INTERPOLATE_H_
#define GOSPP_INTERPOLATE_H_

#include <cmath>

namespace gos {
namespace interpolate {

template<T>
T linear(const T& y1, const T& y2, const T& mu) {
  return y1 * (1.0 - mu) + y2 * mu;
}

T cosine(const T& y1, const T& y2, const T& mu) {

}

} // namespace interpolate
} // namespace gos

#endif
