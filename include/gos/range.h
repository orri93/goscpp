#ifndef GOSPP_RANGE_H_
#define GOSPP_RANGE_H_

#include <limits>

namespace gos {
namespace range {

template<typename T = double>
class d1 {
public:
  d1() : _from(), _to() {}
  d1(const d1& d1) : _from(d1._from), _to(d1._to) {}
  d1(const T& from, const T& to) : _from(from), _to(to) {}

  d1& operator=(const d1& d1) {
    if (this != &d1) {
      _from = d1._from;
      _to = d1._to;
    }
    return *this;
  }

  void setfrom(const T& from) { _from = from; }
  void setto(const T& to) { _to = to; }

  const T& from() const { return _from; }
  const T& to() const { return _to; }

  T difference() {
    return _to - _from;
  }

  void reset() {
    _from = ::std::numeric_limits<T>::max();
    _to = ::std::numeric_limits<T>::min();
  }

  void reset(const T& minimum, const T& maximum) {
    _from = maximum;
    _to = minimum;
  }

  void update(const T& value) {
    if (value < _from) {
      _from = value;
    }
    if (value > _to) {
      _to = value;
    }
  }

private:
  T _from;
  T _to;
};

template<typename T = double>
d1<T> make_d1(const T& from, const T& to) {
  return d1<T>(from, to);
}

} // namespace range
} // namespace gos

#endif
