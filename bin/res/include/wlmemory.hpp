#pragma once

#define ___WYS_API_MEMORY_H___ true

#include "wltype.hpp"

namespace wys
{

  void *memcpy(void *dest, const void *src, size_t count)
  {
    unsigned char *d = static_cast<unsigned char *>(dest);
    const unsigned char *s = static_cast<const unsigned char *>(src);
    while (count--)
    {
      *d++ = *s++;
    }
    return dest;
  }

  template <typename TyChar = char>
  size_t strlen(const TyChar *str)
  {
    const TyChar *s = str;
    while (*s != '\0')
    {
      ++s;
    }
    return s - str;
  }

  int memcmp(const void *a, const void *b, size_t len)
  {
    const unsigned char *ptr_a = static_cast<const unsigned char *>(a);
    const unsigned char *ptr_b = static_cast<const unsigned char *>(b);

    while (len--)
    {
      if (*ptr_a != *ptr_b)
      {
        return (*ptr_a < *ptr_b) ? -1 : 1;
      }
      
      ++ptr_a;
      ++ptr_b;
    }
    return 0;
  }
} // namespace wys