#ifndef GOSPP_SCREEN_H_
#define GOSPP_SCREEN_H_

#include <cstddef>

namespace gos {

template<typename T = int, typename S = size_t>
class screen {
public:
  screen() : _width(), _height() {}
  screen(const screen& screen) : _width(screen._width), _height(screen._height) {}
  screen(const T& width, const T& height) : _width(width), _height(height) {}

  screen& operator=(const screen& screen) {
    if (this != &screen) {
      _width = screen._width;
      _height = screen._height;
    }
    return *this;
  }

  void setwidth(const T& width) { _width = width; }
  void setheight(const T& height) { _height = height; }

  const T& width() const { return _width; }
  const T& height() const { return _height; }

  S index(const T& x, const T& y) {
    return x + y * static_cast<S>(_width);
  }

private:
  T _width;
  T _height;
};

template<typename T = double>
screen<T> make_screen(const T& width, const T& height) {
  return screen<T>(width, height);
}

} // namespace gos

#endif
