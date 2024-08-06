#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Windows.h>

namespace filesystem
{

  std::string getExecutableDirectory()
  {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string fullPath(path);
    size_t pos = fullPath.find_last_of("\\/");
    return (std::string::npos == pos) ? "" : fullPath.substr(0, pos);
  }

} // namespace filesystem
