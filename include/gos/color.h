#ifndef GOSPP_COLOR_H_
#define GOSPP_COLOR_H_

#include <cstdint>
#include <cmath>

#include <algorithm>
#include <string>
#include <vector>

#include <gos/types.h>
#include <gos/interpolate.h>

#define GOS_COLOR_GAMMA 0.43

#define GOS_COLOR_MAX_RGB_F 255.0
#define GOS_COLOR_ROUND_RGB_F 255.5

/* Convert each color component from 0..255 to 0..1 */
#define GOS_COLOR_NORMALIZE(c) (((double) ( c ) ) / GOS_COLOR_MAX_RGB_F)

/* Convert each color component from 0..255 to 0..1 */
#define GOS_COLOR_DENORMALIZE(c) ((uint8_t)(GOS_COLOR_ROUND_RGB_F * (c)))

namespace gos {
namespace color {

template<typename T = double>
T min(const T& a, const T& b, const T& c) {
  return ::std::min(a, ::std::min(b, c));
}

template<typename T = double>
T max(const T& a, const T& b, const T& c) {
  return ::std::max(a, ::std::max(b, c));
}

template<typename T = double, typename U = uint8_t>
U hue(T p, T q, T t) {
  if (t < 0.0) t += 1.0;
  if (t > 1.0) t -= 1.0;
  if (t < (1.0 / 6.0)) {
    return GOS_COLOR_DENORMALIZE(p + (q - p) * 6.0 * t);
  }
  if (t < (1.0 / 2.0)) {
    return GOS_COLOR_DENORMALIZE(q);
  }
  if (t < (2.0 / 3.0)) {
    return GOS_COLOR_DENORMALIZE(p + (q - p) * (2.0 / 3.0 - t) * 6.0);
  }
  return GOS_COLOR_DENORMALIZE(p);
}

namespace s {
namespace rgb {
/* Returns a sRGB value in the range [0,1] for linear input in [0,1]. */
template<typename T = double>
T f(const T& x) {
  return x <= 0.0031308 ? x * 12.92 : (1.055 * ::pow(x, 1.0 / 2.4)) - 0.055;
}
/* Returns a linear value in the range [0,1] for sRGB input in [0,255]. */
template<typename T = double>
T i(T x) {
  x /= T(GOS_COLOR_MAX_RGB_F);
  return T(x <= 0.04045 ? x / 12.92 : ::pow((x + 0.055) / 1.055, 2.4));
}
} // namespace rgb
} // namespace s

namespace convert {
namespace rgb {
namespace to {
template<typename T = double, typename U = uint8_t>
void hsl(T& h, T& s, T& l, const U& r, const U& g, const U& b) {
  T minimum, maximum;
  T rd = GOS_COLOR_NORMALIZE(r);
  T gd = GOS_COLOR_NORMALIZE(g);
  T bd = GOS_COLOR_NORMALIZE(b);
#ifdef GOS_COLOR_MIN_MAX_MACRO
  minimum = GOS_COLOR_MIN(rd, gd, bd);
  maximum = GOS_COLOR_MAX(rd, gd, bd);
#else
  minimum = ::gos::color::min<T>(rd, gd, bd);
  maximum = ::gos::color::max<T>(rd, gd, bd);
#endif
  l = (maximum + minimum) / 2.0;
  if (maximum == minimum) {
    h = s = 0.0; // achromatic
  } else {
    T d = maximum - minimum;
    s = (l > 0.5) ?
      (d / (2.0 - maximum - minimum)) :
      (d / (maximum + minimum));
    if (maximum == rd) {
      h = (gd - bd) / d + (gd < bd ? 6.0 : 0.0);
    } else if (maximum == gd) {
      h = (bd - rd) / d + 2.0;
    } else if (maximum == bd) {
      h = (rd - gd) / d + 4.0;
    }
    h /= 6.0;
  }
}
template<typename T = double, typename U = uint8_t>
void hsv(T& h, T& s, T& v, const U& r, const U& g, const U& b) {
  T minimum, maximum;
  T rd = GOS_COLOR_NORMALIZE(r);
  T gd = GOS_COLOR_NORMALIZE(g);
  T bd = GOS_COLOR_NORMALIZE(b);
#ifdef GOS_COLOR_MIN_MAX_MACRO
  maximum = GOS_COLOR_MAX(rd, gd, bd);
  minimum = GOS_COLOR_MIN(rd, gd, bd);
#else
  minimum = ::gos::color::min<T>(rd, gd, bd);
  maximum = ::gos::color::max<T>(rd, gd, bd);
#endif
  v = maximum;
  T d = maximum - minimum;
  s = maximum == 0 ? 0 : d / maximum;
  if (maximum == minimum) {
    h = 0.0; // achromatic
  } else {
    if (maximum == rd) {
      h = (gd - bd) / d + (gd < bd ? 6.0 : 0.0);
    } else if (maximum == gd) {
      h = (bd - rd) / d + 2.0;
    } else if (maximum == bd) {
      h = (rd - gd) / d + 4.0;
    }
    h /= 6.0;
  }
}
} // namespace to
} // namespace rgb

namespace hsl {
namespace to {
template<typename T = double, typename U = uint8_t>
void rgb(U& r, U& g, U& b, const T& h, const T& s, const T& l) {
  if (s == 0.0) {
    r = g = b = GOS_COLOR_DENORMALIZE(l); // achromatic
  } else {
    T q = (l < 0.5) ? (l * (1.0 + s)) : (l + s - l * s);
    T p = 2.0 * l - q;
    r = ::gos::color::hue(p, q, h + 1.0 / 3.0);
    g = ::gos::color::hue(p, q, h);
    b = ::gos::color::hue(p, q, h - 1.0 / 3.0);
  }
}
} // namespace to
} // namespace hsl

namespace hsv {
namespace to {
template<typename T = double, typename U = uint8_t>
void rgb(U& r, U& g, U& b, T h, T s, T v) {
  int i;
  T f, p, q, t;
  i = static_cast<int>(h * 6.0);
  v *= GOS_COLOR_ROUND_RGB_F;
  f = h * 6.0 - i;
  p = v * (1.0 - s);
  q = v * (1.0 - f * s);
  t = v * (1.0 - (1.0 - f) * s);
  switch (i % 6) {
  case 0:
    r = static_cast<U>(v);
    g = static_cast<U>(t);
    b = static_cast<U>(p);
    break;
  case 1:
    r = static_cast<U>(q);
    g = static_cast<U>(v);
    b = static_cast<U>(p);
    break;
  case 2:
    r = static_cast<U>(p);
    g = static_cast<U>(v);
    b = static_cast<U>(t);
    break;
  case 3:
    r = static_cast<U>(p);
    g = static_cast<U>(q);
    b = static_cast<U>(v);
    break;
  case 4:
    r = static_cast<U>(t);
    g = static_cast<U>(p);
    b = static_cast<U>(v);
    break;
  case 5:
    r = static_cast<U>(v);
    g = static_cast<U>(p);
    b = static_cast<U>(q);
    break;
  }
}
} // namespace to
} // namespace hsv
} // namespace convert

template<typename T = double>
class abc {
public:
  abc() : _a(), _b(), _c() {}
  abc(const abc& abc) : _a(abc._a), _b(abc._b), _c(abc._c) {}
  abc(const T& a, const T& b, const T& c) : _a(a), _b(b), _c(c) {}

  abc& operator=(const abc& abc) {
    if (this != &abc) {
      _a = abc._a;
      _b = abc._b;
      _c = abc._c;
    }
    return *this;
  }

  void assign(const T& a, const T& b, const T& c) {
    _a = a;
    _b = b;
    _c = c;
  }

  bool isblack() {
    return _a <= 0 && _b <= 0 && _c <= 0;
  }

  T sum() {
    return _a + _b + _c;
  }

  T brightness(const T& gamma) {
    return ::pow(sum(), gamma);
  }

  abc fa() {
    return abc(
      ::gos::color::s::rgb::f(_a),
      ::gos::color::s::rgb::f(_b),
      ::gos::color::s::rgb::f(_c));
  }

  abc ia() {
    return abc(
      ::gos::color::s::rgb::i(_a),
      ::gos::color::s::rgb::i(_b),
      ::gos::color::s::rgb::i(_c));
  }

  void seta(const T& a) { _a = a; }
  void setb(const T& b) { _b = b; }
  void setc(const T& c) { _c = c; }

  const T& a() const { return _a; }
  const T& b() const { return _b; }
  const T& c() const { return _c; }

private:
  T _a;
  T _b;
  T _c;
};

template<typename T = double>
abc<T> make_abc(const T& a, const T& b, const T& c) {
  return abc<T>(a, b, c);
}

template<typename T = uint8_t>
class rgb {
public:
  rgb() : _r(), _g(), _b() {}
  rgb(const rgb& rgb) : _r(rgb._r), _g(rgb._g), _b(rgb._b) {}
  rgb(const T& r, const T& g, const T& b) : _r(r), _g(g), _b(b) {}
  rgb(const uint32_t& rgb) :
    _r((rgb & 0xff0000) >> 16),
    _g((rgb & 0xff00) >> 8),
    _b(rgb & 0xff) {
  }

  rgb& operator=(const rgb& rgb) {
    if (this != &rgb) {
      _r = rgb._r;
      _g = rgb._g;
      _b = rgb._b;
    }
    return *this;
  }

  void assign(const T& r, const T& g, const T& b) {
    _r = r;
    _g = g;
    _b = b;
  }

  void assign(const uint32_t& rgb) {
    _r = (rgb & 0xff0000) >> 16;
    _g = (rgb & 0xff00) >> 8;
    _b = rgb & 0xff;
  }

  bool assign(::std::string text) {
    size_t l = text.length();
    if (l > 0 && text.at(0) == '#') {
      text = text.substr(1);
      l--;
    }
    if (l > 0) {
      long n = strtol(text.c_str(), NULL, 16);
      assign(n);
      return true;
    }
    return false;
  }

  void setr(const T& r) { _r = r; }
  void setg(const T& g) { _g = g; }
  void setb(const T& b) { _b = b; }

  const T& r() const { return _r; }
  const T& g() const { return _g; }
  const T& b() const { return _b; }

private:
  T _r;
  T _g;
  T _b;
};

template<typename T = uint8_t>
::gos::color::rgb<T> make_rgb(const T& r, const T& g, const T& b) {
  return ::gos::color::rgb<T>(r, g, b);
}

template<typename T = uint8_t>
::gos::color::rgb<T> make_rgb(const uint32_t& rgb) {
  return ::gos::color::rgb<T>(rgb);
}

template<typename T = double, typename U = uint8_t>
abc<T> normalize(const rgb<U>& rgb) {
  return abc<T>(
    GOS_COLOR_NORMALIZE(rgb.r()),
    GOS_COLOR_NORMALIZE(rgb.g()),
    GOS_COLOR_NORMALIZE(rgb.b()));
}

template<typename T = double, typename U = uint8_t>
rgb<U> denormalize(const abc<T>& abc) {
  return rgb<U>(
    GOS_COLOR_DENORMALIZE(abc.a()),
    GOS_COLOR_DENORMALIZE(abc.b()),
    GOS_COLOR_DENORMALIZE(abc.c()));
}

namespace s {
template<typename T = double, typename U = uint8_t>
abc<T> fa(const ::gos::color::rgb<U>& rgb) {
  return abc<T>(
    ::gos::color::s::rgb::f(rgb.r()),
    ::gos::color::s::rgb::f(rgb.g()),
    ::gos::color::s::rgb::f(rgb.b()));
}
template<typename T = double, typename U = uint8_t>
abc<T> ia(const ::gos::color::rgb<U>& rgb) {
  return abc<T>(
    ::gos::color::s::rgb::i(rgb.r()),
    ::gos::color::s::rgb::i(rgb.g()),
    ::gos::color::s::rgb::i(rgb.b()));
}
} // namespace s

namespace interpolate {
template<typename T = double>
abc<T> linear(const abc<T>& c1, const abc<T>& c2, const double& f) {
  return abc<T>(
    ::gos::interpolate::linear(c1.a(), c2.a(), f),
    ::gos::interpolate::linear(c1.b(), c2.b(), f),
    ::gos::interpolate::linear(c1.c(), c2.c(), f));
}
} // namespace interpolate

namespace perceptual {
template<typename T = uint8_t>
void steps(
  ::std::vector<rgb<T>>& crgbo,
  const rgb<T>& crgb1,
  const rgb<T>& crgb2,
  const int& steps,
  const double& gamma) {
  int i;
  double bright1, bright2, intensity, ratio, sum;
  ::gos::color::abc<> s, c, cs1, cs2;
  cs1 = ::gos::color::s::ia(crgb1);
  cs2 = ::gos::color::s::ia(crgb2);
  bright1 = cs1.brightness(gamma);
  bright2 = cs2.brightness(gamma);
  for (i = 0; i < steps; i++) {
    ratio = (double)i / (double)steps;
    intensity = ::pow(
      ::gos::interpolate::linear(bright1, bright2, ratio),
      1.0 / gamma);
    c = ::gos::color::interpolate::linear(cs1, cs2, ratio);
    if (!c.isblack()) {
      sum = c.sum();
      c.seta(intensity * c.a() / sum);
      c.setb(intensity * c.b() / sum);
      c.setc(intensity * c.c() / sum);
    }
    s = c.fa();
    crgbo.push_back(::gos::color::denormalize(s));
  }
}
} // namespace perceptual

namespace gradient {
template<typename T = uint8_t>
void create(
  ::std::vector<rgb<T>>& gradient,
  const ::std::vector<rgb<T>>& stops,
  const ::std::vector<int>& sizes,
  const double& gamma) {
  size_t count = ::std::min(stops.size(), sizes.size());
  for (size_t i = 0; i < count - 1; i++) {
    ::gos::color::perceptual::steps(
      gradient,
      stops.at(i),
      stops.at(i + 1),
      sizes.at(i),
      gamma);
  }
}
} // namespace gradient

} // namespace color
} // namespace gos

#endif
