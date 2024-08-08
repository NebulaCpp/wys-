#pragma once

#define ___WYS_API_IO_H___ true

#include <Windows.h>
#include "wltype.hpp"
#include "wlstring.hpp"
#include "wlmemory.hpp"

namespace wys
{
  void printf(const string &_Str)
  {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD bytesWritten;
    WriteConsoleA(hCons, _Str.c_str(), _Str.size(), &bytesWritten, NULL);
  }

  struct wfile
  {
    HANDLE handle;
    bool isOpen;

    wfile() : handle(INVALID_HANDLE_VALUE), isOpen(false) {}
  };

  bool open(wfile &file, const wys::string &filePath, bool createIfNotExist = true)
  {
    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    DWORD dwCreationDisposition = createIfNotExist ? OPEN_ALWAYS : OPEN_EXISTING;
    DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

    file.handle = CreateFileA(
        filePath.c_str(),
        dwDesiredAccess,
        dwShareMode,
        NULL,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        NULL);

    file.isOpen = (file.handle != INVALID_HANDLE_VALUE);
    return file.isOpen;
  }

  void close(wfile &file)
  {
    if (file.isOpen)
    {
      CloseHandle(file.handle);
      file.isOpen = false;
    }
  }

  string read(wfile &file)
  {
    if (!file.isOpen)
    {
      return wys::string();
    }

    const size_t initialBufferSize = 64;
    size_t bufferSize = initialBufferSize;
    char *buffer = new char[bufferSize];
    DWORD bytesRead = 0;

    bool endOfWord = false;
    size_t index = 0;

    while (!endOfWord)
    {
      BOOL result = ReadFile(file.handle, buffer + index, 1, &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      if (bytesRead > 0)
      {
        if (buffer[index] == ' ' || buffer[index] == '\n')
        {
          endOfWord = true;
        }
        else
        {
          index++;
          if (index >= bufferSize)
          {
            bufferSize *= 1.2;
            char *newBuffer = new char[bufferSize];
            memcpy(newBuffer, buffer, index);
            delete[] buffer;
            buffer = newBuffer;
          }
        }
      }
    }

    buffer[index] = '\0';
    string result = buffer;
    delete[] buffer;
    return result;
  }

  string getline(wfile &file)
  {
    if (!file.isOpen)
    {
      return string();
    }

    const size_t initialBufferSize = 256;
    size_t bufferSize = initialBufferSize;
    char *buffer = new char[bufferSize];
    DWORD bytesRead = 0;

    size_t index = 0;

    while (true)
    {
      BOOL result = ReadFile(file.handle, buffer + index, 1, &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      if (bytesRead > 0)
      {
        if (buffer[index] == '\n')
        {
          index++;
          break;
        }
        else
        {
          index++;
          if (index >= bufferSize)
          {
            bufferSize *= 1.2;
            char *newBuffer = new char[bufferSize];
            memcpy(newBuffer, buffer, index);
            delete[] buffer;
            buffer = newBuffer;
          }
        }
      }
    }

    buffer[index] = '\0';
    string result = buffer;
    delete[] buffer;
    return result;
  }

  string input()
  {
    const size_t initialBufferSize = 256;
    size_t bufferSize = initialBufferSize;
    char *buffer = new char[bufferSize];
    DWORD bytesRead;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    BOOL result = ReadFile(hStdIn, buffer, bufferSize - 1, &bytesRead, NULL);

    if (!result || bytesRead == 0)
    {
      delete[] buffer;
      return wys::string();
    }

    size_t index = 0;
    while (index < bytesRead)
    {
      if (buffer[index] == '\n')
      {
        index++;
        break;
      }
      index++;
      if (index >= bufferSize - 1)
      {
        bufferSize *= 1.2;
        char *newBuffer = new char[bufferSize];
        memcpy(newBuffer, buffer, index);
        delete[] buffer;
        buffer = newBuffer;
      }
    }

    buffer[index] = '\0';
    wys::string resultString = buffer;
    delete[] buffer;
    return resultString;
  }

  string inputl(size_t line_count)
  {
    if (line_count == 0)
    {
      return wys::string();
    }

    size_t bufferSize = 256;
    char *buffer = new char[bufferSize];
    size_t totalSize = 0;
    size_t lineCount = 0;
    DWORD bytesRead;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    while (lineCount < line_count)
    {
      BOOL result = ReadFile(hStdIn, buffer + totalSize, bufferSize - totalSize - 1, &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      totalSize += bytesRead;
      buffer[totalSize] = '\0';

      for (size_t i = 0; i < totalSize; ++i)
      {
        if (buffer[i] == '\n')
        {
          lineCount++;
        }
        if (lineCount >= line_count)
        {
          buffer[i + 1] = '\0';
          break;
        }
      }

      if (totalSize >= bufferSize - 1)
      {
        bufferSize = static_cast<size_t>(bufferSize * 1.2);
        char *newBuffer = new char[bufferSize];
        memcpy(newBuffer, buffer, totalSize);
        delete[] buffer;
        buffer = newBuffer;
      }
    }

    string resultString(buffer);
    delete[] buffer;
    return resultString;
  }

  bool write(wfile &file, const string &_Str)
  {
    if (!file.isOpen)
    {
      return false;
    }

    DWORD bytesWritten;
    BOOL result = WriteFile(file.handle, _Str.c_str(), static_cast<DWORD>(_Str.size()), &bytesWritten, NULL);
    return result && (bytesWritten == _Str.size());
  }

#pragma region wide strings

  wstring winput()
  {
    const size_t initialBufferSize = 256;
    size_t bufferSize = initialBufferSize;
    wchar_t *buffer = new wchar_t[bufferSize];
    DWORD bytesRead;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    BOOL result = ReadFile(hStdIn, buffer, (bufferSize - 1) * sizeof(wchar_t), &bytesRead, NULL);

    if (!result || bytesRead == 0)
    {
      delete[] buffer;
      return wstring();
    }

    size_t index = 0;
    while (index < (bytesRead / sizeof(wchar_t)))
    {
      if (buffer[index] == L'\n')
      {
        index++;
        break;
      }
      index++;
      if (index >= bufferSize - 1)
      {
        bufferSize = static_cast<size_t>(bufferSize * 1.2);
        wchar_t *newBuffer = new wchar_t[bufferSize];
        memcpy(newBuffer, buffer, index * sizeof(wchar_t));
        delete[] buffer;
        buffer = newBuffer;
      }
    }

    buffer[index] = L'\0';
    wstring wresult = buffer;
    delete[] buffer;
    return wresult;
  }

  wstring winputl(size_t line_count)
  {
    if (line_count == 0)
    {
      return wstring();
    }

    size_t bufferSize = 256;
    wchar_t *buffer = new wchar_t[bufferSize];
    size_t totalSize = 0;
    size_t lineCount = 0;
    DWORD bytesRead;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    while (lineCount < line_count)
    {
      BOOL result = ReadFile(hStdIn, &buffer[totalSize], (bufferSize - totalSize - 1) * sizeof(wchar_t), &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      totalSize += bytesRead / sizeof(wchar_t);
      buffer[totalSize] = L'\0';

      for (size_t i = 0; i < totalSize; ++i)
      {
        if (buffer[i] == L'\n')
        {
          lineCount++;
        }
        if (lineCount >= line_count)
        {
          buffer[i + 1] = L'\0';
          break;
        }
      }

      if (totalSize >= bufferSize - 1)
      {
        bufferSize = static_cast<size_t>(bufferSize * 1.2);
        wchar_t *newBuffer = new wchar_t[bufferSize];
        memcpy(newBuffer, buffer, totalSize * sizeof(wchar_t));
        delete[] buffer;
        buffer = newBuffer;
      }
    }

    wstring result(buffer);
    delete[] buffer;
    return result;
  }

  void wprintf(const wstring &_Str)
  {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD bytesWritten;
    WriteConsoleW(hCons, _Str.c_str(), _Str.size(), &bytesWritten, NULL);
  }

  bool wopen(wfile &file, const wstring &filePath, bool createIfNotExist = true)
  {
    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    DWORD dwCreationDisposition = createIfNotExist ? OPEN_ALWAYS : OPEN_EXISTING;
    DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

    file.handle = CreateFileW(
        filePath.c_str(),
        dwDesiredAccess,
        dwShareMode,
        NULL,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        NULL);

    file.isOpen = (file.handle != INVALID_HANDLE_VALUE);
    return file.isOpen;
  }

  wstring wread(wfile &file)
  {
    if (!file.isOpen)
    {
      return wstring();
    }

    const size_t initialBufferSize = 64;
    size_t bufferSize = initialBufferSize;
    wchar_t *buffer = new wchar_t[bufferSize];
    DWORD bytesRead = 0;

    bool endOfWord = false;
    size_t index = 0;

    while (!endOfWord)
    {
      BOOL result = ReadFile(file.handle, &buffer[index], sizeof(wchar_t), &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      if (bytesRead > 0)
      {
        if (buffer[index] == L' ' || buffer[index] == L'\n')
        {
          endOfWord = true;
        }
        else
        {
          index++;
          if (index >= bufferSize)
          {
            bufferSize = static_cast<size_t>(bufferSize * 1.2);
            wchar_t *newBuffer = new wchar_t[bufferSize];
            memcpy(newBuffer, buffer, index * sizeof(wchar_t));
            delete[] buffer;
            buffer = newBuffer;
          }
        }
      }
    }

    buffer[index] = L'\0';
    wstring result = buffer;
    delete[] buffer;
    return result;
  }

  wstring wgetline(wfile &file)
  {
    if (!file.isOpen)
    {
      return wstring();
    }

    const size_t initialBufferSize = 256;
    size_t bufferSize = initialBufferSize;
    wchar_t *buffer = new wchar_t[bufferSize];
    DWORD bytesRead = 0;

    size_t index = 0;

    while (true)
    {
      BOOL result = ReadFile(file.handle, &buffer[index], sizeof(wchar_t), &bytesRead, NULL);

      if (!result || bytesRead == 0)
      {
        break;
      }

      if (bytesRead > 0)
      {
        if (buffer[index] == L'\n')
        {
          index++;
          break;
        }
        else
        {
          index++;
          if (index >= bufferSize)
          {
            bufferSize = static_cast<size_t>(bufferSize * 1.2);
            wchar_t *newBuffer = new wchar_t[bufferSize];
            memcpy(newBuffer, buffer, index * sizeof(wchar_t));
            delete[] buffer;
            buffer = newBuffer;
          }
        }
      }
    }

    buffer[index] = L'\0';
    wstring result = buffer;
    delete[] buffer;
    return result;
  }

  bool wwrite(wfile &file, const wstring &_Str)
  {
    if (!file.isOpen)
    {
      return false;
    }

    DWORD bytesWritten;
    BOOL result = WriteFile(file.handle, _Str.c_str(), static_cast<DWORD>(_Str.size() * sizeof(wchar_t)), &bytesWritten, NULL);
    return result && (bytesWritten == _Str.size() * sizeof(wchar_t));
  }

#pragma endregion

} // namespace wys
