#include <cctype>
#include <cwchar>
#include <cwctype>

#include <gos/text.h>

namespace gos {
namespace text {

namespace are {
namespace all {

bool digits(const ::std::string& text) {
  bool result = true;
  for (char ch : text) {
    if (!(result &= ::isdigit(ch) > 0)) {
      break;
    }
  }
  return result;
}

bool digitsorperiod(const ::std::string& text) {
  bool result = true;
  for (char ch : text) {
    if (!(result &= (::isdigit(ch) > 0 || ch == '.'))) {
      break;
    }
  }
  return result;
}

bool wdigits(const ::std::wstring& text) {
  bool result = true;
  for (wchar_t ch : text) {
    if (!(result &= ::iswdigit(ch) > 0)) {
      break;
    }
  }
  return result;
}

bool wdigitsorperiod(const ::std::wstring& text) {
  bool result = true;
  for (wchar_t ch : text) {
    if (!(result &= (::iswdigit(ch) > 0 || ch == L'.'))) {
      break;
    }
  }
  return result;
}

} // namespace all
} // namespace are

} // namespace text
} // namespace gos
