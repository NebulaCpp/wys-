#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "strings.hpp"
#include "fstring.hpp"
#include "creators.hpp"


std::string handle_args(const std::string &line)
{
  std::istringstream iss(line);
  std::string word, result;

  while (std::getline(iss, word, ','))
  {
    size_t end = word.find(':');
    if (end == std::string::npos)
    {
      std::cerr << "[wys]: > Wys! <compiler>: <error>: Missing token\n"
                   "  | Make sure to declare arguments like this: <name>: <type>\n"
                   "  | line: "
                << line << '\n';
      return "";
    }

    std::string arg = word.substr(0, end);
    std::string type = word.substr(end + 1);

    if (!result.empty())
    {
      result += ", ";
    }
    result += type + ' ' + arg;
  }

  return result;
}

void handle_var(std::istringstream &iss, std::ofstream &of)
{
  std::string line;
  std::getline(iss, line);

  size_t name_end = line.find(':');
  size_t type_end = line.find('=', name_end + 1);

  if (name_end == std::string::npos || type_end == std::string::npos)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <error>: Missing token\n"
                 "  | make sure to declare variables like this: var <name>: <type> = <value>\n"
                 "  | line: "
              << line << '\n';
    return;
  }

  std::string name = line.substr(0, name_end);
  std::string type = line.substr(name_end + 1, type_end - (name_end + 1));
  std::string value = line.substr(type_end + 1);
  new_var(name, type, value, of);
}

void handle_func(std::istringstream &iss, std::ofstream &of)
{
  std::string line;
  std::getline(iss, line);

  size_t name_end = line.find('(');
  size_t arg_end = line.find(')', name_end + 1);
  size_t type_beg = line.find('(', arg_end + 1);
  size_t type_end = line.find(')', type_beg + 1);

  if (name_end == std::string::npos || arg_end == std::string::npos || type_beg == std::string::npos || type_end == std::string::npos)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <error>: Missing token\n"
                 "  | make sure to declare functions like this: function name(args...)(type):\n"
                 "  | line: "
              << line << '\n';
    return;
  }

  std::string name = line.substr(0, name_end);
  std::string args = line.substr(name_end + 1, arg_end - (name_end + 1));
  std::string type = line.substr(type_beg + 1, type_end - (type_beg + 1));

  std::string formatted_args = handle_args(args);
  new_func(name, formatted_args, type, of);
}

void handle_struct(std::istringstream &iss, std::ofstream &of)
{
  std::string name;
  iss >> name;
  new_struct(name, of);
  blank++;
}

void handle_end(std::istringstream &iss, std::ofstream &of)
{
  blank--;
  of << Blank() << "};\n";
}

void handle_if(std::istringstream &iss, std::ofstream &of)
{
  std::string condition;
  std::getline(iss, condition);
  condition.pop_back();
  of << Blank() << "if (" << condition << ") {\n";
  blank++;
}

void handle_elif(std::istringstream &iss, std::ofstream &of)
{
  blank--;
  std::string condition;
  std::getline(iss, condition);
  condition.pop_back();
  of << Blank() << "} else if (" << condition << ") {\n";
  blank++;
}

void handle_else(std::istringstream &iss, std::ofstream &of)
{
  blank--;
  std::string line;
  std::getline(iss, line);
  of << Blank() << "} else {\n";
  blank++;
}

void handle_include(std::istringstream &iss, std::ofstream &of)
{
  std::string line;
  std::getline(iss, line);

  size_t beg = line.find('\'');
  size_t end = line.find('\'', beg + 1);

  if (beg == std::string::npos || end == std::string::npos)
  {
    std::cerr << "[wys]: > Wys! <compiler>: <error>: Missing token\n"
                 "  | include looks like this: import f'<filename>'\n  | line: "
              << line << '\n';
  }

  std::string file = trim_copy(line.substr(beg + 1, end - (beg + 1)));
  of << "#include \"" << file << "\"\n";
}

void handle_try(std::istringstream &iss, std::ofstream &of)
{
  of << Blank() << "try {\n";
  blank++;
}

void handle_catch(std::istringstream &iss, std::ofstream &of)
{
  blank--;
  of << Blank() << "} catch (...) {\n";
  blank++;
}

void handle_while(std::istringstream &iss, std::ofstream &of)
{
  std::string condition;
  std::getline(iss, condition);

  of << Blank() << "while (" << condition << ") {\n";
  blank++;
}

void handle_for(std::istringstream &iss, std::ofstream &of)
{
  std::string condition;
  std::getline(iss, condition);
  
  trim(condition);

  if (condition.back() == ':')
  {
    condition.pop_back();
  }

  of << Blank() << "for " << condition << " {\n";
  blank++;
}

void handle_throw(std::istringstream &iss, std::ofstream &of)
{
  std::string line;
  std::getline(iss, line);
  of << Blank() << "throw " << line << "\n";
}

void handle_continue(std::istringstream &iss, std::ofstream &of)
{
  of << Blank() << "continue;\n";
}

void handle_break(std::istringstream &iss, std::ofstream &of)
{
  of << Blank() << "break;\n";
}

void def_handles(std::unordered_map<std::string, std::function<void(std::istringstream &, std::ofstream &)>> &handlers)
{
  handlers["var"] = handle_var;
  handlers["function"] = handle_func;
  handlers["struct"] = handle_struct;
  handlers["end"] = handle_end;
  handlers["if"] = handle_if;
  handlers["elif"] = handle_elif;
  handlers["else"] = handle_else;
  handlers["else:"] = handle_else;
  handlers["include"] = handle_include;
  handlers["throw"] = handle_throw;
  handlers["for"] = handle_for;
  handlers["while"] = handle_while;
  handlers["try"] = handle_try;
  handlers["try:"] = handle_try;
  handlers["catch"] = handle_catch;
  handlers["catch:"] = handle_catch;
}

void includes(std::ofstream &output_file)
{
  output_file
      << "#include \"wlerror.hpp\"\n"
      << "#include \"wlio.hpp\"\n"
      << "#include \"wlvector.hpp\"\n"
      << "#include \"wlmemory.hpp\"\n"
      << "#include \"wlstring.hpp\"\n"
      << "#include \"wltype.hpp\"\n"
      << "#include \"wlutiles.hpp\"\n"
      << "using namespace wys;\n"
      << "extern \"C\" {\n";
}