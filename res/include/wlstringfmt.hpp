#pragma once

#define ___WYS_API_STRING_FORMAT_H___ true

#include "wlmemory.hpp"
#include "wltype.hpp"
#include "wlerror.hpp"
#include "wlstring.hpp"
#include <cstdarg>

namespace wys
{
  template <typename TyChar>
  class basic_string_format
  {
  public:
    // Format specifiers
    enum class FormatType
    {
      NONE,
      INT,
      LONG_LONG,
      UNSIGNED_LONG_LONG,
      LONG_DOUBLE,
      BOOL,
      STRING
    };

    basic_string_format() = default;

    basic_string<TyChar> format(const basic_string<TyChar> &fmt, ...) const
    {
      va_list args;
      va_start(args, fmt);

      basic_string<TyChar> result;
      size_t pos = 0;
      while (pos < fmt.size())
      {
        if (fmt[pos] == '{')
        {
          pos++;
          if (pos < fmt.size() && fmt[pos] == '}')
          {
            result += get_next_arg(args, FormatType::STRING);
            pos++;
          }
          else
          {
            throw wys::exception("Unmatched '{' in format string\n");
          }
        }
        else if (fmt[pos] == '%')
        {
          pos++;
          FormatType type = parse_format_specifier(fmt, pos);
          result += get_next_arg(args, type);
        }
        else
        {
          result += fmt[pos++];
        }
      }

      va_end(args);
      return result;
    }

  private:
    FormatType parse_format_specifier(const basic_string<TyChar> &fmt, size_t &pos) const
    {
      // Skip '%' and any additional characters
      while (pos < fmt.size() && fmt[pos] == '%')
      {
        pos++;
      }
      // Implement parsing logic here
      if (pos < fmt.size())
      {
        switch (fmt[pos])
        {
        case 'd':
          return FormatType::INT;
        case 'l':
          if (pos + 1 < fmt.size() && fmt[pos + 1] == 'l')
          {
            pos++;
            return FormatType::LONG_LONG;
          }
          break;
        case 'u':
          if (pos + 1 < fmt.size() && fmt[pos + 1] == 'l' && pos + 2 < fmt.size() && fmt[pos + 2] == 'l')
          {
            pos += 2;
            return FormatType::UNSIGNED_LONG_LONG;
          }
          break;
        case 'f':
          return FormatType::LONG_DOUBLE;
        case 'b':
          return FormatType::BOOL;
        case 's':
          return FormatType::STRING;
        default:
          throw wys::exception("Unknown format specifier\n");
        }
      }
      return FormatType::NONE;
    }

    basic_string<TyChar> get_next_arg(va_list &args, FormatType type) const
    {
      switch (type)
      {
      case FormatType::INT:
        return to_string(va_arg(args, int));
      case FormatType::LONG_LONG:
        return to_string(va_arg(args, long long));
      case FormatType::UNSIGNED_LONG_LONG:
        return to_string(va_arg(args, unsigned long long));
      case FormatType::LONG_DOUBLE:
        return to_string(va_arg(args, long double));
      case FormatType::BOOL:
        return to_string(va_arg(args, int) != 0); // bool is passed as int
      case FormatType::STRING:
        return to_string(va_arg(args, basic_string<TyChar>));
      default:
        throw wys::exception("Unsupported format type\n");
      }
    }

    basic_string<TyChar> to_string(int value) const
    {
      char buffer[32];
      int len = int_to_string(value, buffer, sizeof(buffer));
      return basic_string<TyChar>(buffer, len);
    }

    basic_string<TyChar> to_string(long long value) const
    {
      char buffer[64];
      int len = long_long_to_string(value, buffer, sizeof(buffer));
      return basic_string<TyChar>(buffer, len);
    }

    basic_string<TyChar> to_string(unsigned long long value) const
    {
      char buffer[64];
      int len = unsigned_long_long_to_string(value, buffer, sizeof(buffer));
      return basic_string<TyChar>(buffer, len);
    }

    basic_string<TyChar> to_string(long double value) const
    {
      char buffer[64];
      int len = long_double_to_string(value, buffer, sizeof(buffer));
      return basic_string<TyChar>(buffer, len);
    }

    basic_string<TyChar> to_string(bool value) const
    {
      return value ? basic_string<TyChar>("true") : basic_string<TyChar>("false");
    }

    basic_string<TyChar> to_string(const basic_string<TyChar> &str) const
    {
      return str;
    }

    int int_to_string(int value, char *buffer, size_t buffer_size) const
    {
      int len = 0;
      bool negative = value < 0;
      if (negative)
        value = -value;

      do
      {
        if (len >= buffer_size - 1)
          return len; // Buffer overflow
        buffer[len++] = '0' + (value % 10);
        value /= 10;
      } while (value != 0);

      if (negative)
        buffer[len++] = '-';
      reverse_buffer(buffer, len);
      buffer[len] = '\0';
      return len;
    }

    int long_long_to_string(long long value, char *buffer, size_t buffer_size) const
    {
      int len = 0;
      bool negative = value < 0;
      if (negative)
        value = -value;

      do
      {
        if (len >= buffer_size - 1)
          return len; // Buffer overflow
        buffer[len++] = '0' + (value % 10);
        value /= 10;
      } while (value != 0);

      if (negative)
        buffer[len++] = '-';
      reverse_buffer(buffer, len);
      buffer[len] = '\0';
      return len;
    }

    int unsigned_long_long_to_string(unsigned long long value, char *buffer, size_t buffer_size) const
    {
      int len = 0;

      do
      {
        if (len >= buffer_size - 1)
          return len; // Buffer overflow
        buffer[len++] = '0' + (value % 10);
        value /= 10;
      } while (value != 0);

      reverse_buffer(buffer, len);
      buffer[len] = '\0';
      return len;
    }

    int long_double_to_string(long double value, char *buffer, size_t buffer_size) const
    {
      int len = 0;
      int int_part = static_cast<int>(value);
      long double frac_part = value - int_part;
      len += int_to_string(int_part, buffer, buffer_size);

      if (len >= buffer_size - 1)
        return len;
      buffer[len++] = '.';

      frac_part *= 10;
      for (int i = 0; i < 6; ++i) // Limit precision to 6 decimal places
      {
        int digit = static_cast<int>(frac_part) % 10;
        if (len >= buffer_size - 1)
          return len; // Buffer overflow
        buffer[len++] = '0' + digit;
        frac_part = (frac_part - digit) * 10;
      }

      buffer[len] = '\0';
      return len;
    }

    void reverse_buffer(char *buffer, int len) const
    {
      for (int i = 0; i < len / 2; ++i)
      {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
      }
    }
  };

  using string_format = basic_string_format<char>;
  using wstring_format = basic_string_format<wchar_t>;
  using string16_format = basic_string_format<char16_t>;
  using string32_format = basic_string_format<char32_t>;
}
