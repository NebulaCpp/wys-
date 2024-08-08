#pragma once

#include "wlxstring.hpp"
#include "wlerror.hpp"
#include "wlmemory.hpp"

namespace wys
{
  void reverse(char *str, int length)
  {
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
      char temp = str[start];
      str[start] = str[end];
      str[end] = temp;
      start++;
      end--;
    }
  }

  basic_string<char> float_to_string(long double value)
  {
    static char str[50];
    int i = 0;

    if (value == 0.0)
    {
      str[i++] = '0';
      str[i] = '\0';
      return str;
    }

    long long intPart = (long long)value;
    long double fracPart = value - intPart;

    if (intPart < 0)
    {
      str[i++] = '-';
      intPart = -intPart;
    }

    char intStr[20];
    int j = 0;
    do
    {
      intStr[j++] = (intPart % 10) + '0';
      intPart /= 10;
    } while (intPart > 0);

    reverse(intStr, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = intStr[k];
    }

    if (fracPart > 0)
    {
      str[i++] = '.';
      fracPart *= 10;
      for (int k = 0; k < 9; k++)
      {
        int digit = (int)fracPart;
        str[i++] = digit + '0';
        fracPart -= digit;
        fracPart *= 10;
      }
    }

    str[i] = '\0';
    return basic_string<char>(str);
  }

  basic_string<char> int_to_string(long long value)
  {
    static char str[25];
    int i = 0;

    if (value == 0)
    {
      str[i++] = '0';
      str[i] = '\0';
      return str;
    }

    int isNegative = 0;
    if (value < 0)
    {
      isNegative = 1;
      value = -value;
    }

    char temp[20];
    int j = 0;
    while (value > 0)
    {
      temp[j++] = (value % 10) + '0';
      value /= 10;
    }

    if (isNegative)
    {
      str[i++] = '-';
    }

    reverse(temp, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = temp[k];
    }

    str[i] = '\0';
    return basic_string<char>(str);
  }

  basic_string<char> uint_to_string(unsigned long long value)
  {
    static char str[25];
    int i = 0;

    if (value == 0)
    {
      str[i++] = '0';
      str[i] = '\0';
      return str;
    }

    char temp[20];
    int j = 0;
    while (value > 0)
    {
      temp[j++] = (value % 10) + '0';
      value /= 10;
    }

    reverse(temp, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = temp[k];
    }

    str[i] = '\0';
    return basic_string<char>(str);
  }

  void wreverse(wchar_t *str, int length)
  {
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
      wchar_t temp = str[start];
      str[start] = str[end];
      str[end] = temp;
      start++;
      end--;
    }
  }

  basic_string<wchar_t> float_to_wstring(long double value)
  {
    static wchar_t str[50];
    int i = 0;

    if (value == 0.0)
    {
      str[i++] = L'0';
      str[i] = L'\0';
      return str;
    }

    long long intPart = (long long)value;
    long double fracPart = value - intPart;

    if (intPart < 0)
    {
      str[i++] = L'-';
      intPart = -intPart;
    }

    wchar_t intStr[20];
    int j = 0;
    do
    {
      intStr[j++] = (intPart % 10) + L'0';
      intPart /= 10;
    } while (intPart > 0);

    wreverse(intStr, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = intStr[k];
    }

    if (fracPart > 0)
    {
      str[i++] = L'.';
      fracPart *= 10;
      for (int k = 0; k < 9; k++)
      {
        int digit = (int)fracPart;
        str[i++] = digit + L'0';
        fracPart -= digit;
        fracPart *= 10;
      }
    }

    str[i] = L'\0';
    return basic_string<wchar_t>(str);
  }

  basic_string<wchar_t> int_to_wstring(long long value)
  {
    static wchar_t str[25];
    int i = 0;

    if (value == 0)
    {
      str[i++] = L'0';
      str[i] = L'\0';
      return str;
    }

    int isNegative = 0;
    if (value < 0)
    {
      isNegative = 1;
      value = -value;
    }

    wchar_t temp[20];
    int j = 0;
    while (value > 0)
    {
      temp[j++] = (value % 10) + L'0';
      value /= 10;
    }

    if (isNegative)
    {
      str[i++] = L'-';
    }

    wreverse(temp, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = temp[k];
    }

    str[i] = L'\0';
    return basic_string<wchar_t>(str);
  }

  basic_string<wchar_t> uint_to_wstring(unsigned long long value)
  {
    static wchar_t str[25];
    int i = 0;

    if (value == 0)
    {
      str[i++] = L'0';
      str[i] = L'\0';
      return str;
    }

    wchar_t temp[20];
    int j = 0;
    while (value > 0)
    {
      temp[j++] = (value % 10) + L'0';
      value /= 10;
    }

    wreverse(temp, j);
    for (int k = 0; k < j; k++)
    {
      str[i++] = temp[k];
    }

    str[i] = L'\0';
    return basic_string<wchar_t>(str);
  }
} // namespace wys
