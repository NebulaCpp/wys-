#pragma once

#include "wlxstring.hpp"
#include "wlerror.hpp"

namespace wys
{
  inline long double stold(const wys::basic_string<char> &str)
  {
    long double result = 0.0;
    bool negative = false;
    size_t i = 0;

    // Gestion du signe
    if (str.size() > 0 && str[0] == '-')
    {
      negative = true;
      ++i;
    }
    else if (str.size() > 0 && str[0] == '+')
    {
      ++i;
    }

    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - '0');
      ++i;
    }

    if (i < str.size() && str[i] == '.')
    {
      ++i;
      long double divisor = 10.0;
      while (i < str.size() && str[i] >= '0' && str[i] <= '9')
      {
        result += (str[i] - '0') / divisor;
        divisor *= 10;
        ++i;
      }
    }

    return negative ? -result : result;
  }

  inline long long stoll(const wys::basic_string<char> &str)
  {
    long long result = 0;
    bool negative = false;
    size_t i = 0;

    if (str.size() > 0 && str[0] == '-')
    {
      negative = true;
      ++i;
    }
    else if (str.size() > 0 && str[0] == '+')
    {
      ++i;
    }

    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - '0');
      ++i;
    }

    return negative ? -result : result;
  }

  inline unsigned long long stoull(const wys::basic_string<char> &str)
  {
    unsigned long long result = 0;
    size_t i = 0;

    if (str.size() > 0 && str[0] == '-')
    {
      throw wys::exception("stoull does not support negative values");
    }
    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
    {
      result = result * 10 + (str[i] - '0');
      ++i;
    }

    return result;
  }

  inline long double wstold(const wys::basic_string<wchar_t> &str)
  {
    long double result = 0.0;
    bool negative = false;
    size_t i = 0;

    if (str.size() > 0 && str[0] == L'-')
    {
      negative = true;
      ++i;
    }
    else if (str.size() > 0 && str[0] == L'+')
    {
      ++i;
    }

    while (i < str.size() && str[i] >= L'0' && str[i] <= L'9')
    {
      result = result * 10 + (str[i] - L'0');
      ++i;
    }

    if (i < str.size() && str[i] == L'.')
    {
      ++i;
      long double divisor = 10.0;
      while (i < str.size() && str[i] >= L'0' && str[i] <= L'9')
      {
        result += (str[i] - L'0') / divisor;
        divisor *= 10;
        ++i;
      }
    }

    return negative ? -result : result;
  }

  inline long long wstoll(const wys::basic_string<wchar_t> &str)
  {
    long long result = 0;
    bool negative = false;
    size_t i = 0;

    if (str.size() > 0 && str[0] == L'-')
    {
      negative = true;
      ++i;
    }
    else if (str.size() > 0 && str[0] == L'+')
    {
      ++i;
    }

    while (i < str.size() && str[i] >= L'0' && str[i] <= L'9')
    {
      result = result * 10 + (str[i] - L'0');
      ++i;
    }

    return negative ? -result : result;
  }

  inline unsigned long long wstoull(const wys::basic_string<wchar_t> &str)
  {
    unsigned long long result = 0;
    size_t i = 0;

    if (str.size() > 0 && str[0] == L'-')
    {
      throw wys::exception("stoull does not support negative values");
    }

    while (i < str.size() && str[i] >= L'0' && str[i] <= L'9')
    {
      result = result * 10 + (str[i] - L'0');
      ++i;
    }

    return result;
  }

} // namespace wys