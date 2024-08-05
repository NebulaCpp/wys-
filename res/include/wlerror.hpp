#pragma once

#define ___WYS_API_ERROR_H___ true

#include "wlmemory.hpp"

namespace wys
{
  
  class exception 
  {
  protected:
    char *what_;
  public:
    exception(const char *_Err)
    {
      what_ = new char[strlen(_Err)];
      memcpy(what_, _Err, strlen(_Err));
    }

    virtual const char *what()
    {
      return what_;
    }

    ~exception()
    {
      delete[] what_;
    }
  };
} // namespace wys
