#pragma once

#include "wlstring.hpp"

namespace wys
{
  template <typename TyString, typename CharType>
  class basic_stringfmt
  {
  public:
    basic_stringfmt(const TyString &format) : format_string(format) {}

    basic_stringfmt &operator=(const TyString &format)
    {
      format_string = format;
      return *this;
    }

    basic_stringfmt &operator=(const CharType *format)
    {
      format_string = TyString(format);
      return *this;
    }

    basic_stringfmt &operator+=(const TyString &format)
    {
      format_string += format;
      return *this;
    }

    basic_stringfmt &operator+=(const CharType *format)
    {
      format_string += TyString(format);
      return *this;
    }

    template <typename TyValue>
    TyString format(const CharType *placeholder, const TyValue &value)
    {
      TyString result;
      TyString value_str = to_string(value);

      size_t start = 0;
      size_t pos = format_string.find(placeholder, start);

      while (pos != TyString::npos)
      {
        result += format_string.substr(start, pos - start);
        result += value_str;
        start = pos + strlen(placeholder);
        pos = format_string.find(placeholder, start);
      }

      result += format_string.substr(start);

      return result;
    }

  private:
    TyString format_string;

    template <typename Ty>
    TyString to_string(const Ty &value);

    TyString to_string(long long value)
    {
      return int_to_string(value);
    }

    TyString to_string(unsigned long long value)
    {
      return uint_to_string(value);
    }

    TyString to_string(long double value)
    {
      return float_to_string(value);
    }

    TyString to_string(const TyString &str)
    {
      return str;
    }

    TyString to_string(const CharType *str)
    {
      return TyString(str);
    }
  };

  using stringfmt = basic_stringfmt<basic_string<char>, char>;
  using wstringfmt = basic_stringfmt<basic_string<wchar_t>, wchar_t>;

} // namespace wys
