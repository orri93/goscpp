#ifndef GOSPP_SCALE_H_
#define GOSPP_SCALE_H_

#include <gos/range.h>

namespace gos {

template<typename D = double, typename R = double>
class scale {
public:
  scale() {}
  scale(const scale& scale) : _domain(scale._domain), _range(scale._range) {}
  scale(const ::gos::range::d1<D>& domain, const ::gos::range::d1<R>& range) :
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

  void setdomain(const ::gos::range::d1<D>& domain) { _domain = domain; }
  void setrange(const ::gos::range::d1<R>& range) { _range = range; }

  void setdomain(const D& from, const D& to) { _domain.setfrom(from); _domain.setto(to); }
  void setrange(const R& from, const R& to) { _range.setfrom(from); _range.setto(to); }

  const ::gos::range::d1<D>& domain() const { return _domain; }
  const ::gos::range::d1<R>& range() const { return _range; }

  R value(const D& value) {
    D dd = _domain.difference();
    R rd = _range.difference();
    double r = static_cast<double>(value - _domain.from()) / dd;
    return _range.from() + static_cast<R>(r * rd);
  }
  D reverse(const R& value) {
    D dd = _domain.difference();
    R rd = _range.difference();
    double r = static_cast<double>(value - _range.from()) / rd;
    return _domain.from() + static_cast<D>(r * dd);
  }

private:
  ::gos::range::d1<D> _domain;
  ::gos::range::d1<R> _range;
};

template<typename D = double, typename R = double>
scale<D, R> make_scale(const ::gos::range::d1<D>& domain, const ::gos::range::d1<R>& range) {
  return scale<D, R>(domain, range);
}

template<typename D = double, typename R = double>
scale<D, R> make_scale(const D& domain_from, const D& domain_to, const R& range_from, const R& range_to) {
  return scale<D, R>(::gos::range::make_d1(domain_from, domain_to), ::gos::range::make_d1(range_from, range_to));
}

} // namespace gos

#endif
