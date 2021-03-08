#ifndef GOSPP_TIME_H_
#define GOSPP_TIME_H_

#include <chrono>

namespace gos {
namespace time {

namespace nearest {
template<typename T, typename D>
D neighbor(const T& first, const T& second, const T& value) {
  D fd = ::std::chrono::abs(first - value);
  D sd = ::std::chrono::abs(second - value);
  return fd - sd;
}
} // namespace nearest

} // namespace time
} // namespace gos

#endif
