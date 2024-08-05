#pragma once

#define ___WYS_API_UTILES_H___ true

namespace wys
{
  template <typename Ty>
  Ty min(Ty a, Ty b)
  {
    return (a < b) ? a : b;
  }

  template <typename Ty>
  Ty max(Ty a, Ty b)
  {
    return (a > b) ? a : b;
  }

  template <typename Ty>
  Ty pow(Ty base, int exponent)
  {
    Ty result = 1;
    while (exponent > 0)
    {
      if (exponent % 2 == 1)
      {
        result *= base;
      }
      base *= base;
      exponent /= 2;
    }
    return result;
  }

  long double sqrt(double value)
  {
    if (value < 0)
    {
      return -1;
    }

    long double result = value;
    long double epsilon = 0.0000000001;
    
    while ((result - value / result) > epsilon)
    {
      result = (result + value / result) / 2;
    }
    return result;
  }
} // namespace wys
