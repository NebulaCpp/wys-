# Wys! Documentation

## Introduction

Welcome to the documentation for Wys!. This language is designed to be simple and effective but is not intended for beginners. It is compiled to C++ and then to a DLL. A specific loader is required to execute the applications.

## Compilation and Execution

### Compilation

To compile source code written in Wys!, use the provided compiler tool:

```bash
Wys!.exe <input> <output>
```

- `<input>`: Path to the source file.
- `<output>`: Path to the output DLL file (optional).

Ensure that the source file is in the same folder as the binaries for compilation. It is recommended to add this folder to the PATH for easier access to the compilation tools.

### Execution

To run the generated DLL, use the provided loader:

```bash
Wloader!.exe <DLL>
```

- `<DLL>`: Path to the DLL file to be executed.

The DLL file must be located in the same folder as the loader binaries. Also, ensure that the binaries folder is in the PATH for easy access.

## Folder Structure

- **Standard Libraries (WLSTD)**: The files for the standard library are located in `bin/res/include`. These files are automatically included during compilation.
- **API**: The API folder (provided empty) is located in `bin/res/api`. Files in this folder do not need to be explicitly specified during compilation, as the compiler is aware of their path.

## Language Syntax

### Structure Declaration

```plaintext
struct StructName:
  var x: int = 0
end
```

- `struct`: Declares a new structure.
- `var`: Declares a variable within the structure.

### Function Declaration

```plaintext
function FunctionName(Arg1: int, Arg2: double)(int):
  var x: int = 45

  if (Arg1 == 6):
    for (int i = 0; i < 45; ++i):
      printf("Hello ")
    end
    printf("\n")
  elif (Arg1 == 1):
    printf("Ok\n")
  else:
    exit(568)
  end

  x++
  x += 456
  x = 0

  while (false):
    exit(456)
  end

  return Arg1 + Arg2
end
```

- `function`: Declares a new function.
- `var`: Declares a local variable.
- `if`, `elif`, `else`: Conditional statements.
- `for`: For loop.
- `while`: While loop.
- `return`: Returns a value from the function.

## Built-in Functions and Variables

### General

- **`wys::printf(const string &_Str)`**
  - Prints the given string `_Str` to the standard output (console).
  - **Parameters**: 
    - `_Str`: A `string` to be printed.
  - **Returns**: `void`

- **`wys::wprintf(const wstring &_Str)`**
  - Prints the given wide string `_Str` to the standard output (console).
  - **Parameters**: 
    - `_Str`: A `wstring` to be printed.
  - **Returns**: `void`

### File Handling

#### `wys::file` Structure

- **`wys::file`**
  - Represents a file object with a handle and open status.
  - **Members**:
    - `HANDLE handle`: File handle.
    - `bool isOpen`: Indicates whether the file is open.

#### File Operations

- **`wys::open(file &file, const string &filePath, bool createIfNotExist = true)`**
  - Opens or creates a file with the specified path and access mode.
  - **Parameters**:
    - `file`: The `file` object to be used.
    - `filePath`: The path to the file as a `string`.
    - `createIfNotExist`: If `true`, the file is created if it does not exist.
  - **Returns**: `bool` - `true` if the file is successfully opened or created; otherwise, `false`.

- **`wys::close(file &file)`**
  - Closes the file associated with the given `file` object.
  - **Parameters**:
    - `file`: The `file` object to be closed.
  - **Returns**: `void`

- **`wys::read(file &file)`**
  - Reads a word from the open file.
  - **Parameters**:
    - `file`: The `file` object to read from.
  - **Returns**: `string` - The word read from the file.

- **`wys::getline(file &file)`**
  - Reads a line from the open file.
  - **Parameters**:
    - `file`: The `file` object to read from.
  - **Returns**: `string` - The line read from the file.

- **`wys::write(file &file, const string &_Str)`**
  - Writes the given string `_Str` to the open file.
  - **Parameters**:
    - `file`: The `file` object to write to.
    - `_Str`: The `string` to be written.
  - **Returns**: `bool` - `true` if the write operation was successful; otherwise, `false`.

#### Wide String File Operations

- **`wys::wopen(file &file, const wstring &filePath, bool createIfNotExist = true)`**
  - Opens or creates a file with the specified wide string path and access mode.
  - **Parameters**:
    - `file`: The `file` object to be used.
    - `filePath`: The path to the file as a `wstring`.
    - `createIfNotExist`: If `true`, the file is created if it does not exist.
  - **Returns**: `bool` - `true` if the file is successfully opened or created; otherwise, `false`.

- **`wys::wread(file &file)`**
  - Reads a word from the open file using wide characters.
  - **Parameters**:
    - `file`: The `file` object to read from.
  - **Returns**: `wstring` - The word read from the file.

- **`wys::wgetline(file &file)`**
  - Reads a line from the open file using wide characters.
  - **Parameters**:
    - `file`: The `file` object to read from.
  - **Returns**: `wstring` - The line read from the file.

- **`wys::wwrite(file &file, const wstring &_Str)`**
  - Writes the given wide string `_Str` to the open file.
  - **Parameters**:
    - `file`: The `file` object to write to.
    - `_Str`: The `wstring` to be written.
  - **Returns**: `bool` - `true` if the write operation was successful; otherwise, `false`.

#### User Input

- **`wys::input()`**
  - Reads a line of input from the standard input (console) and returns it as a `string`.
  - **Parameters**: None
  - **Returns**: `string` - The input line.

- **`wys::inputl(size_t line_count)`**
  - Reads a specified number of lines from the standard input (console) and returns them as a `string`.
  - **Parameters**:
    - `line_count`: Number of lines to read.
  - **Returns**: `string` - The input lines concatenated.

- **`wys::winput()`**
  - Reads a line of input from the standard input (console) and returns it as a `wstring`.
  - **Parameters**: None
  - **Returns**: `wstring` - The input line.

- **`wys::winputl(size_t line_count)`**
  - Reads a specified number of lines from the standard input (console) and returns them as a `wstring`.
  - **Parameters**:
    - `line_count`: Number of lines to read.
  - **Returns**: `wstring` - The input lines concatenated.

## Built-in Memory Functions

### Memory Operations

- **`wys::memcpy(void *dest, const void *src, size_t count)`**
  - Copies `count` bytes from the source pointer `src` to the destination pointer `dest`.
  - **Parameters**:
    - `dest`: Pointer to the destination buffer where bytes will be copied.
    - `src`: Pointer to the source buffer from which bytes will be copied.
    - `count`: Number of bytes to copy.
  - **Returns**: `void *` - Pointer to the destination buffer (`dest`).

- **`wys::strlen(const TyChar *str)`**
  - Computes the length of a null-terminated string.
  - **Parameters**:
    - `str`: Pointer to the null-terminated string. The type of character can be specified with the template parameter `TyChar` (default is `char`).
  - **Returns**: `size_t` - Length of the string, excluding the null terminator.

- **`wys::memcmp(const void *a, const void *b, size_t len)`**
  - Compares `len` bytes of memory between two blocks pointed to by `a` and `b`.
  - **Parameters**:
    - `a`: Pointer to the first memory block.
    - `b`: Pointer to the second memory block.
    - `len`: Number of bytes to compare.
  - **Returns**: 
    - `0` if the memory blocks are identical.
    - A negative integer if the memory block pointed to by `a` is less than that pointed to by `b`.
    - A positive integer if the memory block pointed to by `a` is greater than that pointed to by `b`.

### Template Function

- **`wys::strlen(const TyChar *str)`**
  - **Template Parameter**: 
    - `TyChar`: The type of characters in the string (default is `char`).
  - **Parameters**:
    - `str`: Pointer to the null-terminated string of type `TyChar`.
  - **Returns**: `size_t` - Length of the string, excluding the null terminator.

## `wlstring.hpp`

### Overview

This header file defines a `basic_string` class template for managing strings and provides a variety of utilities for converting numerical values to strings. It supports both narrow (`char`) and wide (`wchar_t`) character types.

### `basic_string` Class Template

The `basic_string` class template provides a flexible, dynamic string class with various member functions and operators for string manipulation. 

#### Template Parameters
- `TyChar`: The character type for the string (e.g., `char`, `wchar_t`, `char16_t`, `char32_t`).

#### Private Members
- `TyChar *data_`: Pointer to the character array holding the string data.
- `size_t size_`: The current size of the string.
- `size_t capacity_`: The current allocated capacity of the string.

#### Public Member Functions

- **Constructors**
  - `basic_string()`: Default constructor. Initializes an empty string.
  - `basic_string(const TyChar *CharPtr)`: Initializes the string with the given C-style null-terminated string.
  - `basic_string(const basic_string &other)`: Copy constructor.
  - `basic_string(basic_string &&other) noexcept`: Move constructor.

- **Assignment Operators**
  - `basic_string &operator=(const basic_string &other)`: Copy assignment operator.
  - `basic_string &operator=(basic_string &&other) noexcept`: Move assignment operator.

- **Destructor**
  - `~basic_string()`: Destructor. Frees allocated memory.

- **Member Functions**
  - `void append(const TyChar &C)`: Appends a single character to the end of the string.
  - `TyChar pop()`: Removes and returns the last character of the string.
  - `TyChar front() const`: Returns the first character of the string.
  - `TyChar back() const`: Returns the last character of the string.
  - `size_t size() const`: Returns the current size of the string.
  - `const TyChar *c_str() const`: Returns a C-style null-terminated string representation of the `basic_string`.
  - `TyChar operator[](size_t i) const`: Accesses the character at index `i`.

- **Operators**
  - `bool operator==(const basic_string &other) const`: Checks for equality with another `basic_string`.
  - `bool operator!=(const basic_string &other) const`: Checks for inequality with another `basic_string`.
  - `basic_string operator+(const basic_string &other) const`: Concatenates with another `basic_string`.
  - `basic_string operator+(const TyChar *Ch)`: Concatenates with a C-style null-terminated string.
  - `basic_string &operator+=(const basic_string &other)`: Appends another `basic_string` to this one.
  - `basic_string &operator+=(const TyChar *Ch)`: Appends a C-style null-terminated string to this string.

#### Private Functions

- **`void resize(size_t new_size)`**
  - Resizes the string to `new_size`, increasing capacity if necessary.

### Conversion Functions

- **`void reverse(char *str, int length)`**
  - Reverses a null-terminated C-style string.

- **`basic_string<char> long_double_to_string(long double value)`**
  - Converts a `long double` to a `basic_string<char>`.

- **`char *long_long_to_string(long long value)`**
  - Converts a `long long` to a C-style null-terminated string.

- **`basic_string<char> unsigned_long_long_to_string(unsigned long long value)`**
  - Converts an `unsigned long long` to a `basic_string<char>`.

- **`void wreverse(wchar_t *str, int length)`**
  - Reverses a wide-character null-terminated string.

- **`basic_string<wchar_t> long_double_to_wstring(long double value)`**
  - Converts a `long double` to a `basic_string<wchar_t>`.

- **`basic_string<wchar_t> long_long_to_wstring(long long value)`**
  - Converts a `long long` to a `basic_string<wchar_t>`.

- **`basic_string<wchar_t> unsigned_long_long_to_wstring(unsigned long long value)`**
  - Converts an `unsigned long long` to a `basic_string<wchar_t>`.

### Type Aliases

- **`using string = basic_string<char>;`**
- **`using wstring = basic_string<wchar_t>;`**
- **`using ustring = basic_string<unsigned char>;`**
- **`using string16_t = basic_string<char16_t>;`**
- **`using string32_t = basic_string<char32_t>;`**

These aliases simplify the usage of common string types.
