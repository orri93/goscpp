#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/text.h>

namespace gos {
namespace text {

TEST(GosTextTest, AreAllCharDigits) {
  bool areDigits;

  areDigits = are::all::digits("0123456789");
  EXPECT_TRUE(areDigits);

  areDigits = are::all::digits("01bb");
  EXPECT_FALSE(areDigits);

  areDigits = are::all::digits("0.123456789");
  EXPECT_FALSE(areDigits);

  areDigits = are::all::digitsorperiod("0.123456789");
  EXPECT_TRUE(areDigits);

  areDigits = are::all::digitsorperiod("0.1bb");
  EXPECT_FALSE(areDigits);


  areDigits = are::all::wdigits(L"0123456789");
  EXPECT_TRUE(areDigits);

  areDigits = are::all::wdigits(L"01bb");
  EXPECT_FALSE(areDigits);

  areDigits = are::all::wdigits(L"0.123456789");
  EXPECT_FALSE(areDigits);

  areDigits = are::all::wdigitsorperiod(L"0.123456789");
  EXPECT_TRUE(areDigits);

  areDigits = are::all::wdigitsorperiod(L"0.1bb");
  EXPECT_FALSE(areDigits);
}

} // namespace signal
} // namespace gos
