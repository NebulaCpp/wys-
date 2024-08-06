#pragma once

#define ___WYS_API_VECTOR_H___ true

#include "wlmemory.hpp"
#include "wlerror.hpp"
#include "wltype.hpp"
#include "wlutiles.hpp"

namespace wys
{
  template <typename Ty>
  class vector {
  private:
    Ty *data_;
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
        Ty *new_data = new Ty[new_capacity];
        memcpy(new_data, data_, size_ * sizeof(Ty));
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
      }
      size_ = new_size;
    }

  public:
    vector()
      : data_(nullptr), size_(0), capacity_(1)
    {
      data_ = new Ty[1];
    }

    vector(const Ty *CharPtr)
      : data_(nullptr), size_(0), capacity_(0)
    {
      size_ = strlen(CharPtr);
      data_ = new Ty[capacity_];
      memcpy(data_, CharPtr, size_ * sizeof(Ty));
    }

    vector(const vector &other)
      : data_(nullptr), size_(0), capacity_(0)
    {
      size_ = other.size_;
      data_ = new Ty[capacity_];
      memcpy(data_, other.data_, size_ * sizeof(Ty));
    }

    vector(vector &&other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    vector& operator=(const vector &other)
    {
      if (this != &other)
      {
        // Clean up existing resources
        delete[] data_;

        // Allocate new resources and copy data
        size_ = other.size_;
        capacity_ = size_ + 1;
        data_ = new Ty[capacity_];
        memcpy(data_, other.data_, size_ * sizeof(Ty));
      }
      return *this;
    }

    vector& operator=(vector &&other) noexcept
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

    ~vector()
    {
      delete[] data_;
    }

    void append(const Ty &C)
    {
      resize(size_ + 1);
      data_[size_] = C;
    }

    Ty pop()
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot pop from an empty vector\n");
      }
      Ty ch = data_[size_ - 1];
      resize(size_ - 1);
      return ch;
    }

    void push_back(const Ty &C)
    {
      append(C);
    }

    Ty front() const
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot access front of an empty vector\n");
      }
      return data_[0];
    }

    Ty back() const
    {
      if (size_ == 0)
      {
        throw wys::exception("Cannot access back of an empty vector\n");
      }
      return data_[size_ - 1];
    }

    size_t size() const
    {
      return size_;
    }

    size_t capacity() const
    {
      return capacity_;
    }
  };
} // namespace wys
