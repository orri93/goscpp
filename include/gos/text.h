#ifndef GOSPP_TEXT_H_
#define GOSPP_TEXT_H_

#include <string>

namespace gos {
namespace text {

namespace are {
namespace all {

bool digits(const ::std::string& text);
bool digitsorperiod(const ::std::string& text);
bool wdigits(const ::std::wstring& text);
bool wdigitsorperiod(const ::std::wstring& text);
bool hex(const ::std::string& text);
bool whex(const ::std::wstring& text);

} // namespace all
} // namespace are

} // namespace text
} // namespace gos

#endif
