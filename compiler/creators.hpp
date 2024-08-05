#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "fstring.hpp"
#include "strings.hpp"

// Global variable for indentation level
int blank = 0;

// Function to generate indentation based on the current level of blanks
std::string Blank()
{
  std::string buff;
  for (int i = 0; i < blank; ++i)
  {
    buff += '\t';
  }
  return buff;
}

// Functions for handling different types of lines
void new_var(const std::string &name, const std::string &type, const std::string &value, std::ofstream &of)
{
  of << Blank() << type << " " << name << " = " << value << ";\n";
}

void new_func(const std::string &name, const std::string &args, const std::string &type, std::ofstream &of)
{
  of << Blank() << "__declspec(dllexport) " << type << " " << name << "(" << args << ") {\n";
}

void new_struct(std::string &name, std::ofstream &of)
{
  if (name.back() == ':')
  {
    name.pop_back();
  }

  of << Blank() << "struct " << name << " {\n";
}

void new_call(const std::string &fn, const std::string &args, std::ofstream &of)
{
  of << Blank() << fn << "(" << args << ");\n";
}