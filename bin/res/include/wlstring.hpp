#pragma once

#define ___WYS_API_LIB_STRING___ true

#include "wlmemory.hpp"
#include "wltype.hpp"
#include "wlerror.hpp"
#include "wlxstring.hpp"
#include "wlston.hpp" // Wys Lib String To Num
#include "wlntos.hpp" // Wys Lib Num To String

namespace wys
{
  template <typename TyChar>
  class basic_string;

#pragma region String To Num

  long double stold(const wys::basic_string<char> &str);
  long long stoll(const wys::basic_string<char> &str);
  unsigned long long stoull(const wys::basic_string<char> &str);

  long double wstold(const wys::basic_string<wchar_t> &str);
  long long wstoll(const wys::basic_string<wchar_t> &str);
  unsigned long long wstoull(const wys::basic_string<wchar_t> &str);

#pragma endregion

#pragma region Num To String

  void reverse(char *str, int length);
  basic_string<char> float_to_string(long double value);
  basic_string<char> int_to_string(long long value);
  basic_string<char> uint_to_string(unsigned long long value);

  void wreverse(wchar_t *str, int length);
  basic_string<wchar_t> float_to_wstring(long double value);
  basic_string<wchar_t> int_to_wstring(long long value);
  basic_string<wchar_t> uint_to_wstring(unsigned long long value);

#pragma endregion

#pragma region def

  using string = basic_string<char>;
  using wstring = basic_string<wchar_t>;
  using ustring = basic_string<unsigned char>;
  using string16_t = basic_string<char16_t>;
  using string32_t = basic_string<char32_t>;

#pragma endregion
} // namespace wys
