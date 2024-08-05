#pragma once

#include <string>
#include <unordered_map>
#include <regex>

namespace wys
{

  class wfstring
  {
  public:
    wfstring(const std::wstring &format) : format_string(format) {}

    wfstring() = default;

    wfstring &operator=(const std::wstring &fmt)
    {
      format_string = fmt;

      return *this;
    }

    void add_variable(const std::wstring &name, const std::wstring &value)
    {
      variables[name] = value;
    }

    void add_variable(const std::wstring &name, long long value)
    {
      variables[name] = std::to_wstring(value);
    }

    void add_variable(const std::wstring &name, unsigned long long value)
    {
      variables[name] = std::to_wstring(value);
    }

    void add_variable(const std::wstring &name, long double value)
    {
      variables[name] = std::to_wstring(value);
    }

    std::wstring format()
    {
      std::wstring result = format_string;
      std::wregex re(L"\\{(.*?)\\}");
      std::wsmatch match;

      while (std::regex_search(result, match, re))
      {
        std::wstring var_name = match[1].str();
        std::wstring var_value = variables[var_name];
        result.replace(match.position(0), match.length(0), var_value);
      }

      return result;
    }

    void clear()
    {
      format_string.clear();
      variables.clear();
    }

  private:
    std::wstring format_string;
    std::unordered_map<std::wstring, std::wstring> variables;
  };


  class fstring
  {
  public:
    fstring(const std::string &format) : format_string(format) {}
    fstring(const char *format) : format_string(format) {}

    fstring() = default;

    fstring &operator=(const std::string &fmt)
    {
      format_string = fmt;

      return *this;
    }

    fstring &operator=(const char *fmt)
    {
      format_string = fmt;

      return *this;
    }

    void add_variable(const std::string &name, const std::string &value)
    {
      variables[name] = value;
    }

    void add_variable(const std::string &name, long long value)
    {
      variables[name] = std::to_string(value);
    }

    void add_variable(const std::string &name, unsigned long long value)
    {
      variables[name] = std::to_string(value);
    }

    void add_variable(const std::string &name, long double value)
    {
      variables[name] = std::to_string(value);
    }

    std::string format()
    {
      std::string result = format_string;
      std::regex re("\\{(.*?)\\}");
      std::smatch match;

      while (std::regex_search(result, match, re))
      {
        std::string var_name = match[1].str();
        std::string var_value = variables[var_name];
        result.replace(match.position(0), match.length(0), var_value);
      }

      return result;
    }

    void clear()
    {
      format_string.clear();
      variables.clear();
    }

  private:
    std::string format_string;
    std::unordered_map<std::string, std::string> variables;
  };
} // namespace wys

