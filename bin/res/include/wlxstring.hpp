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

    // Method to extract a substring from the string
    basic_string substr(size_t pos = 0, size_t len = -1) const
    {
      if (pos > size_)
      {
        throw wys::exception("Substring position out of range\n");
      }
      if (len == npos || pos + len > size_)
      {
        len = size_ - pos;
      }
      return basic_string(data_ + pos, len);
    }

    // Method to erase a part of the string
    void erase(size_t pos = 0, size_t len = -1)
    {
      if (pos > size_)
      {
        throw wys::exception("Erase position out of range\n");
      }
      if (len == npos || pos + len > size_)
      {
        len = size_ - pos;
      }
      size_t new_size = size_ - len;
      memmove(data_ + pos, data_ + pos + len, (size_ - pos - len) * sizeof(TyChar));
      resize(new_size);
    }

    // Method to find a substring within the string
    size_t find(const basic_string &substr, size_t pos = 0) const
    {
      if (substr.size_ == 0 || pos >= size_)
      {
        return npos;
      }
      if (substr.size_ > size_ - pos)
      {
        return npos;
      }

      for (size_t i = pos; i <= size_ - substr.size_; ++i)
      {
        if (memcmp(data_ + i, substr.data_, substr.size_ * sizeof(TyChar)) == 0)
        {
          return i;
        }
      }
      return npos;
    }

    // Method to get the end iterator (size of the string)
    size_t end() const
    {
      return size_;
    }

    // Additional methods that might be useful
    void clear()
    {
      resize(0);
    }

    bool empty() const
    {
      return size_ == 0;
    }

    size_t npos = -1;
  };
} // namespace wys
