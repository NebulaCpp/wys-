#pragma once

#define ___WYS_API_LIB_STRING___ true

#include "wlmemory.hpp"
#include "wltype.hpp"
#include "wlerror.hpp"

namespace wys
{
  template <typename TyChar>
  class basic_string
  {
  private:
    TyChar *data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_size)
    {
      if (new_size >= capacity_)
      {
        size_t new_capacity = static_cast<size_t>(capacity_ * 1.2); // Growth strategy: 20% increase
        if (new_capacity <= new_size)
        {
          new_capacity = new_size + 1; // Ensure enough capacity for the new size
        }
        TyChar *new_data = new TyChar[new_capacity];
        memcpy(new_data, data_, size_ * sizeof(TyChar));
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
      }
      size_ = new_size;
      data_[size_] = '\0'; // Ensure null-termination
    }

  public:
    basic_string()
        : data_(nullptr), size_(0), capacity_(0)
    {
    }

    basic_string(const TyChar *CharPtr)
        : data_(nullptr), size_(0), capacity_(0)
    {
      size_ = strlen(CharPtr);
      capacity_ = size_ + 1; // For null-termination
      data_ = new TyChar[capacity_];
      memcpy(data_, CharPtr, size_ * sizeof(TyChar));
      data_[size_] = '\0'; // Ensure null-termination
    }

    basic_string(const basic_string &other)
        : data_(nullptr), size_(0), capacity_(0)
    {
      size_ = other.size_;
      capacity_ = size_ + 1;
      data_ = new TyChar[capacity_];
      memcpy(data_, other.data_, size_ * sizeof(TyChar));
      data_[size_] = '\0'; // Ensure null-termination
    }

    basic_string(basic_string &&other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    basic_string &operator=(const basic_string &other)
    {
      if (this != &other)
      {
        // Clean up existing resources
        delete[] data_;

        // Allocate new resources and copy data
        size_ = other.size_;
        capacity_ = size_ + 1;
        data_ = new TyChar[capacity_];
        memcpy(data_, other.data_, size_ * sizeof(TyChar));
        data_[size_] = '\0'; // Ensure null-termination
      }
      return *this;
    }

    basic_string &operator=(basic_string &&other) noexcept
    {
      if (this != &other)
      {
        // Clean up existing resources
        delete[] data_;

        // Steal resources from the other object
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        // Reset the other object
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
      }
      return *this;
    }

    ~basic_string()
    {
      delete[] data_;
    }

    void append(const TyChar &C)
    {
      resize(size_ + 1);
      data_[size_ - 1] = C;
      data_[size_] = '\0'; // Ensure null-termination
    }

    TyChar pop()
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot pop from an empty string\n");
      }
      TyChar ch = data_[size_ - 1];
      resize(size_ - 1);
      return ch;
    }

    TyChar front() const
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot access front of an empty string\n");
      }
      return data_[0];
    }

    TyChar back() const
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot access back of an empty string\n");
      }
      return data_[size_ - 1];
    }

    size_t size() const
    {
      return size_;
    }

    const TyChar *c_str() const
    {
      return data_;
    }

    TyChar operator[](size_t i) const
    {
      if (i >= size_)
      {
        throw wys::exception("Index out of range\n");
      }
      return data_[i];
    }

    bool operator==(const basic_string &other) const
    {
      if (size_ != other.size_)
        return false;
      return memcmp(data_, other.data_, size_ * sizeof(TyChar)) == 0;
    }

    bool operator!=(const basic_string &other) const
    {
      return !(*this == other);
    }

    basic_string operator+(const basic_string &other) const
    {
      basic_string result;
      result.resize(size_ + other.size_);
      memcpy(result.data_, data_, size_ * sizeof(TyChar));
      memcpy(result.data_ + size_, other.data_, other.size_ * sizeof(TyChar));
      return result;
    }

    basic_string operator+(const TyChar *Ch)
    {
      size_t len = strlen(Ch);
      basic_string result;
      result.resize(size_ + len);
      memcpy(result.data_, data_, size_ * sizeof(TyChar));
      memcpy(result.data_ + size_, Ch, len * sizeof(TyChar));
      return result;
    }

    basic_string &operator+=(const basic_string &other)
    {
      size_t new_size = size_ + other.size_;
      resize(new_size);
      memcpy(data_ + size_ - other.size_, other.data_, other.size_ * sizeof(TyChar));
      return *this;
    }

    basic_string &operator+=(const TyChar *Ch)
    {
      size_t len = strlen(Ch);
      size_t new_size = size_ + len;
      resize(new_size);
      memcpy(data_ + size_ - len, Ch, len * sizeof(TyChar));
      return *this;
    }
  };

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

  basic_string<char> long_double_to_string(long double value)
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

  char *long_long_to_string(long long value)
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
    return str;
  }

  basic_string<char> unsigned_long_long_to_string(unsigned long long value)
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

  basic_string<wchar_t> long_double_to_wstring(long double value)
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

  basic_string<wchar_t> long_long_to_wstring(long long value)
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

  basic_string<wchar_t> unsigned_long_long_to_wstring(unsigned long long value)
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

#pragma region def

  using string = basic_string<char>;
  using wstring = basic_string<wchar_t>;
  using ustring = basic_string<unsigned char>;
  using string16_t = basic_string<char16_t>;
  using string32_t = basic_string<char32_t>;

#pragma endregion
} // namespace wys
