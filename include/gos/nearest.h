#ifndef GOSPP_NEAREST_H_
#define GOSPP_NEAREST_H_

namespace gos {
namespace nearest {

template<T>
T neighbor(const T& first, const T& second, const T& value) {
  T fd = first - value;
  T sd = second - value;
  return fd * fd - sd * sd;
}

} // namespace nearest
} // namespace gos

#endif
