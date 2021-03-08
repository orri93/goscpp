#ifndef GOSPP_SCALE_H_
#define GOSPP_SCALE_H_

#include <gos/range.h>

namespace gos {

template<typename T = double>
class scale {
public:
  scale() {}
  scale(const scale& scale) : _domain(scale._domain), _range(scale._range) {}
  scale(const ::gos::range::d1<T>& domain, const ::gos::range::d1<T>& range) :
    _domain(domain),
    _range(range) {
  }

  scale& operator=(const scale& scale) {
    if (this != &scale) {
      _domain = scale._domain;
      _range = scale._range;
    }
    return *this;
  }

  void setdomain(const ::gos::range::d1<T>& domain) { _domain = domain; }
  void setrange(const ::gos::range::d1<T>& range) { _range = range; }

  void setdomain(const T& from, const T& to) { _domain.setfrom(from); _domain.setto(to); }
  void setrange(const T& from, const T& to) { _range.setfrom(from); _range.setto(to); }

  const ::gos::range::d1<T>& domain() const { return _domain; }
  const ::gos::range::d1<T>& range() const { return _range; }

  T value(const T& value) {
    T dd = _domain.difference();
    T rd = _range.difference();
    T r = (value - _domain.from()) / dd;
    return _range.from() + r * rd;
  }
  T reverse(const T& value) {
    T dd = _domain.difference();
    T rd = _range.difference();
    T r = (value - _range.from()) / rd;
    return _domain.from() + r * dd;
  }

private:
  ::gos::range::d1<T> _domain;
  ::gos::range::d1<T> _range;
};

template<typename T = double>
scale<T> make_scale(const ::gos::range::d1<T>& domain, const ::gos::range::d1<T>& range) {
  return scale<T>(domain, range);
}

template<typename T = double>
scale<T> make_scale(const T& domain_from, const T& domain_to, const T& range_from, const T& range_to) {
  return scale<T>(::gos::range::make_d1(domain_from, domain_to), ::gos::range::make_d1(range_from, range_to));
}

} // namespace gos

#endif
