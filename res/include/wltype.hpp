#pragma once

#define ___WYS_API_TYPE_H___ true

typedef unsigned long long size_t;
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef int int32;
typedef float float32;

namespace wys
{
  template <typename TyA, typename TyB>
  struct pair
  {
    TyA first;
    TyB second;
  };

  template <typename Ty>
  struct _2D_Elem
  {
    Ty x;
    Ty y;
  };
} // namespace wys
