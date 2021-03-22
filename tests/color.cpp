#include <cstdint>

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/interpolate.h>
#include <gos/color.h>

#define GOS_COLOR_UNIT_TEST_COUNT 64

namespace gos {
namespace color {

TEST(GosColorTest, Text) {
  uint32_t color;
  ::std::string text;
  bool result;

  text = "#07049b";
  result = ::gos::color::from::text(color, text);
  EXPECT_TRUE(result);
  EXPECT_EQ(0x07049b, color);

  text = "f4ec04";
  result = ::gos::color::from::text(color, text);
  EXPECT_TRUE(result);
  EXPECT_EQ(0xf4ec04, color);

  text = "lightgrey";
  result = ::gos::color::from::text(color, text);
  EXPECT_TRUE(result);
  EXPECT_EQ(0xd3d3d3, color);

  text = "hotpink";
  result = ::gos::color::from::text(color, text);
  EXPECT_TRUE(result);
  EXPECT_EQ(0xff69b4, color);

  text = "AliceBlue";
  result = ::gos::color::from::text(color, text);
  EXPECT_TRUE(result);
  EXPECT_EQ(0xf0f8ff, color);
}

TEST(GosColorTest, Assign) {
  ::gos::color::abc<> c;
  ::gos::color::rgb<> rgb;

  c.assign(0.1, 0.2, 0.3);
  EXPECT_DOUBLE_EQ(0.1, c.a());
  EXPECT_DOUBLE_EQ(0.2, c.b());
  EXPECT_DOUBLE_EQ(0.3, c.c());

  rgb.assign(0x07, 0x04, 0x9b); /* Dark blue */
  EXPECT_EQ(0x07, rgb.r());
  EXPECT_EQ(0x04, rgb.g());
  EXPECT_EQ(0x9b, rgb.b());
  rgb.assign(0xf4, 0xec, 0x04); /* Yellow */
  EXPECT_EQ(0xf4, rgb.r());
  EXPECT_EQ(0xec, rgb.g());
  EXPECT_EQ(0x04, rgb.b());
  rgb.assign(0x07049b); /* Dark blue */
  EXPECT_EQ(0x07, rgb.r());
  EXPECT_EQ(0x04, rgb.g());
  EXPECT_EQ(0x9b, rgb.b());
  rgb.assign(0xf4ec04); /* Yellow */
  EXPECT_EQ(0xf4, rgb.r());
  EXPECT_EQ(0xec, rgb.g());
  EXPECT_EQ(0x04, rgb.b());

  rgb.assign("#07049b"); /* Dark blue */
  EXPECT_EQ(0x07, rgb.r());
  EXPECT_EQ(0x04, rgb.g());
  EXPECT_EQ(0x9b, rgb.b());
  rgb.assign("f4ec04"); /* Yellow */
  EXPECT_EQ(0xf4, rgb.r());
  EXPECT_EQ(0xec, rgb.g());
  EXPECT_EQ(0x04, rgb.b());
  rgb.assign("AliceBlue"); /* Named Color */
  EXPECT_EQ(0xf0, rgb.r());
  EXPECT_EQ(0xf8, rgb.g());
  EXPECT_EQ(0xff, rgb.b());
}

TEST(GosColorTest, IsBlack) {
  ::gos::color::abc<> c;
  bool rb;

  c = abc<>(0.0, 0.0, 0.0);
  rb = c.isblack();
  EXPECT_TRUE(rb);

  c.seta(0.01);
  rb = c.isblack();
  EXPECT_FALSE(rb);

  c.seta(-0.01);
  rb = c.isblack();
  EXPECT_TRUE(rb);

  c.seta(0.0);
  c.setb(0.01);
  c.setc(0.0);
  rb = c.isblack();
  EXPECT_FALSE(rb);

  c.seta(0.0);
  c.setb(0.0);
  c.setc(0.01);
  rb = c.isblack();
  EXPECT_FALSE(rb);

  c.seta(0.01);
  c.setb(0.0);
  c.setc(0.01);
  rb = c.isblack();
  EXPECT_FALSE(rb);

  c.seta(0.01);
  c.setb(0.01);
  c.setc(0.01);
  rb = c.isblack();
  EXPECT_FALSE(rb);

  c.seta(1.0);
  c.setb(1.0);
  c.setc(1.0);
  rb = c.isblack();
  EXPECT_FALSE(rb);
}

TEST(GosColorTest, Sum) {
  const int max = 32;
  ::gos::color::abc<> c;
  double rd;
  int ai, bi, ci;

  c = abc<>(0.0, 0.0, 0.0);
  rd = c.sum();
  EXPECT_DOUBLE_EQ(0.0, rd);

  c.seta(0.01);
  c.setb(0.02);
  c.setc(0.03);
  rd = c.sum();
  EXPECT_DOUBLE_EQ(0.06, rd);

  for (ai = 0; ai < max; ai++) {
    for (bi = 0; bi < max; bi++) {
      for (ci = 0; ci < max; ci++) {
        c.seta(static_cast<double>(ai));
        c.setb(static_cast<double>(bi));
        c.setc(static_cast<double>(ci));
        rd = c.sum();
        EXPECT_DOUBLE_EQ(c.a() + c.b() + c.c(), rd);
      }
    }
  }
}

TEST(GosColorTest, Brightness) {
  const double Gamma = GOS_COLOR_GAMMA;
  ::gos::color::abc<> c;
  double br;

  c = abc<>(0.0, 0.0, 0.0);
  br = c.brightness(Gamma);
  EXPECT_DOUBLE_EQ(0.0, br);

  c.seta(0.01);
  c.setb(0.02);
  c.setc(0.03);
  br = c.brightness(Gamma);
  EXPECT_DOUBLE_EQ(0.29826688434994880, br);

  //for (ir = 0; ir < maxrgb; ir++) {
  //  for (ig = 0; ig < maxrgb; ig++) {
  //    for (ib = 0; ib < maxrgb; ib++) {
  //    }
  //  }
  //}
}

TEST(GosColorTest, SRGBf) {
  const int Max = 10000;
  int i;
  double y, x, r;

  x = 0.0;
  y = ::gos::color::s::rgb::f(x);
  EXPECT_DOUBLE_EQ(0.0, y);

  x = 0.0031300;
  y = ::gos::color::s::rgb::f(x);
  EXPECT_DOUBLE_EQ(0.040439599999999999, y);

  x = 0.0031308;
  y = ::gos::color::s::rgb::f(x);
  EXPECT_DOUBLE_EQ(0.040449935999999999, y);

  x = 0.0031310;
  y = ::gos::color::s::rgb::f(x);
  EXPECT_DOUBLE_EQ(0.040452448050838648, y);

  for (i = 0; i < Max; i++) {
    r = (double)i / (double)Max;
    y = ::gos::color::s::rgb::f(r);
    EXPECT_GE(1.0, y);
    EXPECT_LE(0.0, y);
  }
}

TEST(GosColorTest, SRGBi) {
  const int Max = 256;
  int i;
  double y, x;

  x = 0.0;
  y = ::gos::color::s::rgb::i(x);
  EXPECT_DOUBLE_EQ(0.0, y);

  x = 5.0;
  y = ::gos::color::s::rgb::i(x);
  EXPECT_DOUBLE_EQ(0.0015176349177441874, y);

  x = 10.0;
  y = ::gos::color::s::rgb::i(x);
  EXPECT_DOUBLE_EQ(0.0030352698354883748, y);

  x = 15.0;
  y = ::gos::color::s::rgb::i(x);
  EXPECT_DOUBLE_EQ(0.0047769534806937292, y);

  for (i = 0; i < Max; i++) {
    y = ::gos::color::s::rgb::i((double)i);
    EXPECT_GE(1.0, y);
    EXPECT_LE(0.0, y);
  }
}

TEST(GosColorTest, SRGBfa) {
  const int Max = 100;
  double xi, xj, xk, yi, yj, yk;
  int i, j, k;
  ::gos::color::abc<> x, y;

  for (i = 0; i < Max; i++) {
    for (j = 0; j < Max; j++) {
      for (k = 0; k < Max; k++) {
        xi = (double)i / (double)Max;
        xj = (double)j / (double)Max;
        xk = (double)k / (double)Max;
        yi = ::gos::color::s::rgb::f(xi);
        yj = ::gos::color::s::rgb::f(xj);
        yk = ::gos::color::s::rgb::f(xk);
        x.seta(xi);
        x.setb(xj);
        x.setc(xk);
        y = x.fa();
        EXPECT_DOUBLE_EQ(yi, y.a());
        EXPECT_DOUBLE_EQ(yj, y.b());
        EXPECT_DOUBLE_EQ(yk, y.c());
      }
    }
  }
}

TEST(GosColorTest, SRGBia) {
  const int Max = 256;
  double xi, xj, xk, yi, yj, yk;
  int i, j, k;
  ::gos::color::abc<> y;
  ::gos::color::rgb<> x;

  for (i = 0; i < Max; i++) {
    for (j = 0; j < Max; j++) {
      for (k = 0; k < Max; k++) {
        xi = (double)i;
        xj = (double)j;
        xk = (double)k;
        yi = ::gos::color::s::rgb::i(xi);
        yj = ::gos::color::s::rgb::i(xj);
        yk = ::gos::color::s::rgb::i(xk);
        x.setr(i);
        x.setg(j);
        x.setb(k);
        y = ::gos::color::s::ia(x);
        EXPECT_DOUBLE_EQ(yi, y.a());
        EXPECT_DOUBLE_EQ(yj, y.b());
        EXPECT_DOUBLE_EQ(yk, y.c());
      }
    }
  }
}

TEST(GosColorTest, Normalize) {
  const int Max = 256;
  int i, j, k;
  double n;
  ::gos::color::abc<> c;
  ::gos::color::rgb<> rgb;

  for (i = 0; i < Max; i++) {
    n = GOS_COLOR_NORMALIZE(i);
    EXPECT_GE(1.0, n);
    EXPECT_LE(0.0, n);
  }
  for (i = 0; i < Max; i++) {
    for (j = 0; j < Max; j++) {
      for (k = 0; k < Max; k++) {
        rgb.setr(i);
        rgb.setg(j);
        rgb.setb(k);
        c = ::gos::color::normalize(rgb);
        n = GOS_COLOR_NORMALIZE(i);
        EXPECT_DOUBLE_EQ(n, c.a());
        n = GOS_COLOR_NORMALIZE(j);
        EXPECT_DOUBLE_EQ(n, c.b());
        n = GOS_COLOR_NORMALIZE(k);
        EXPECT_DOUBLE_EQ(n, c.c());
      }
    }
  }
}

TEST(GosColorTest, Denormalize) {
  const int Max = 10;
  int i, j, k, n;
  double r, ri, rj, rk;
  uint8_t u;
  ::gos::color::abc<> c;
  ::gos::color::rgb<> rgb;

  for (i = 0; i < Max; i++) {
    r = (double)i / (double)Max;
    n = GOS_COLOR_DENORMALIZE(r);
    EXPECT_GE(255, n);
    EXPECT_LE(0, n);
  }
  for (i = 0; i < Max; i++) {
    for (j = 0; j < Max; j++) {
      for (k = 0; k < Max; k++) {
        ri = (double)i / (double)Max;
        rj = (double)j / (double)Max;
        rk = (double)k / (double)Max;
        c.seta(ri);
        c.setb(rj);
        c.setc(rk);
        rgb = ::gos::color::denormalize(c);
        u = GOS_COLOR_DENORMALIZE(ri);
        EXPECT_EQ(u, rgb.r());
        u = GOS_COLOR_DENORMALIZE(rj);
        EXPECT_EQ(u, rgb.g());
        u = GOS_COLOR_DENORMALIZE(rk);
        EXPECT_EQ(u, rgb.b());
      }
    }
  }
}

TEST(GosColorTest, Interpolate) {
  const int Max = 1000;
  int i;
  double r, y;
  ::gos::color::abc<>  co, c1, c2;
  c1.seta(0.03);
  c1.setb(0.06);
  c1.setc(0.11);
  c2.seta(0.68);
  c2.setb(0.79);
  c2.setc(0.93);
  for (i = 0; i < Max; i++) {
    r = (double)i / (double)Max;
    co = ::gos::color::interpolate::linear(c1, c2, r);
    y = ::gos::interpolate::linear(c1.a(), c2.a(), r);
    EXPECT_DOUBLE_EQ(y, co.a());
    y = ::gos::interpolate::linear(c1.b(), c2.b(), r);
    EXPECT_DOUBLE_EQ(y, co.b());
    y = ::gos::interpolate::linear(c1.c(), c2.c(), r);
    EXPECT_DOUBLE_EQ(y, co.c());
  }
}

TEST(GosColorTest, PerceptualSteps) {
  const double Gamma = GOS_COLOR_GAMMA;
  const int Count = GOS_COLOR_UNIT_TEST_COUNT;
  std::vector<::gos::color::rgb<>> c;
  ::gos::color::rgb<> c1, c2;
  int i;

  /* Dark blue */
  c1.assign(0x07, 0x04, 0x9b);

  /* Yellow */
  c2.assign(0xf4, 0xec, 0x04);

  ::gos::color::perceptual::steps(c, c1, c2, Count, Gamma);
  i = 0;
  for (const ::gos::color::rgb<>& ca : c) {
    EXPECT_LE(c1.r(), ca.r());
    EXPECT_GE(c2.r(), ca.r());

    EXPECT_LE(c1.g(), ca.g());
    EXPECT_GE(c2.g(), ca.g());

    EXPECT_LE(c2.b(), ca.b());
    EXPECT_GE(c1.b(), ca.b());
    i++;
  }
  EXPECT_EQ(Count, i);
}

TEST(GosColorTest, CreateGradient) {
  std::vector<int> gradientsize;
  std::vector<::gos::color::rgb<>> stops;
  std::vector<::gos::color::rgb<>> gradient;

  stops.push_back(::gos::color::make_rgb(0x07049b));  /* Dark blue */
  stops.push_back(::gos::color::make_rgb(0x02f7f3));  /* Cyan */
  stops.push_back(::gos::color::make_rgb(0x09f725));  /* Green */
  stops.push_back(::gos::color::make_rgb(0xf4ec04));  /* Yellow */
  stops.push_back(::gos::color::make_rgb(0xf79d01));  /* Orange */
  stops.push_back(::gos::color::make_rgb(0x8c0101));  /* Dark red */

  gradientsize.push_back(10);
  gradientsize.push_back(20);
  gradientsize.push_back(30);
  gradientsize.push_back(40);
  gradientsize.push_back(50);

  ::gos::color::gradient::create(gradient, stops, gradientsize, GOS_COLOR_GAMMA);

  EXPECT_EQ(10 + 20 + 30 + 40 + 50, gradient.size());
}

TEST(GosColorTest, HSL) {
  const int maxrgb = 256;
  const double step = 0.01;
  int ir, ig, ib;
  double h, s, l;
  uint8_t r, g, b, cr, cg, cb;
  for (ir = 0; ir < maxrgb; ir++) {
    for (ig = 0; ig < maxrgb; ig++) {
      for (ib = 0; ib < maxrgb; ib++) {
        r = (uint8_t)ir;
        g = (uint8_t)ig;
        b = (uint8_t)ib;
        ::gos::color::convert::rgb::to::hsl(h, s, l, r, g, b);
        ::gos::color::convert::hsl::to::rgb(cr, cg, cb, h, s, l);
        EXPECT_EQ(r, cr);
        EXPECT_EQ(g, cg);
        EXPECT_EQ(b, cb);
      }
    }
  }
}

TEST(GosColorTest, HSV) {
  const int maxrgb = 256;
  const double step = 0.01;
  int ir, ig, ib;
  double h, s, v;
  uint8_t r, g, b, cr, cg, cb;
  for (ir = 0; ir < maxrgb; ir++) {
    for (ig = 0; ig < maxrgb; ig++) {
      for (ib = 0; ib < maxrgb; ib++) {
        r = (uint8_t)ir;
        g = (uint8_t)ig;
        b = (uint8_t)ib;
        ::gos::color::convert::rgb::to::hsv(h, s, v, r, g, b);
        ::gos::color::convert::hsv::to::rgb(cr, cg, cb, h, s, v);
        EXPECT_EQ(r, cr);
        EXPECT_EQ(g, cg);
        EXPECT_EQ(b, cb);
      }
    }
  }
}

TEST(GosColorTest, RGB2HSL) {
  double h, s, l;
  ::gos::color::convert::rgb::to::hsl(h, s, l, 0x00, 0x00, 0x00);
  EXPECT_DOUBLE_EQ(0.0, h);
  EXPECT_DOUBLE_EQ(0.0, s);
  EXPECT_DOUBLE_EQ(0.0, l);

  ::gos::color::convert::rgb::to::hsl(h, s, l, 0xff, 0xff, 0xff);
  EXPECT_DOUBLE_EQ(0.0, h);
  EXPECT_DOUBLE_EQ(0.0, s);
  EXPECT_DOUBLE_EQ(1.0, l);
}

TEST(GosColorTest, RGB2HSV) {
  double h, s, v;

  ::gos::color::convert::rgb::to::hsv(h, s, v, 0x00, 0x00, 0x00);
  EXPECT_DOUBLE_EQ(0.0, h);
  EXPECT_DOUBLE_EQ(0.0, s);
  EXPECT_DOUBLE_EQ(0.0, v);

  ::gos::color::convert::rgb::to::hsv(h, s, v, 0xff, 0xff, 0xff);
  EXPECT_DOUBLE_EQ(0.0, h);
  EXPECT_DOUBLE_EQ(0.0, s);
  EXPECT_DOUBLE_EQ(1.0, v);
}

TEST(GosColorTest, HSL2RGB) {
  uint8_t r, g, b;

  ::gos::color::convert::hsl::to::rgb(r, g, b, 0.0, 0.0, 0.0);
  EXPECT_EQ(0x00, r);
  EXPECT_EQ(0x00, g);
  EXPECT_EQ(0x00, b);

  ::gos::color::convert::hsl::to::rgb(r, g, b, 1.0, 1.0, 1.0);
  EXPECT_EQ(0xff, r);
  EXPECT_EQ(0xff, g);
  EXPECT_EQ(0xff, b);
}

TEST(GosColorTest, HSV2RGB) {
  uint8_t r, g, b;

  ::gos::color::convert::hsv::to::rgb(r, g, b, 0.0, 0.0, 0.0);
  EXPECT_EQ(0x00, r);
  EXPECT_EQ(0x00, g);
  EXPECT_EQ(0x00, b);

  ::gos::color::convert::hsv::to::rgb(r, g, b, 1.0, 1.0, 1.0);
  EXPECT_EQ(0xff, r);
  EXPECT_EQ(0x00, g);
  EXPECT_EQ(0x00, b);
}

TEST(GosColorTest, Hue2RGB) {
  uint8_t value;

  value = ::gos::color::hue(0.0, 0.0, 0.0);
  EXPECT_EQ(0, value);

  value = ::gos::color::hue(1.0, 1.0, 1.0);
  EXPECT_EQ(0xff, value);
}

} // namespace color
} // namespace gos
