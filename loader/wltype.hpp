#pragma once

#define ___WYS_API_TYPE_H___ true

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
