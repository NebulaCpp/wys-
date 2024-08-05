#include <iostream>
#include <windows.h>
#include "wlstring.hpp"  // Ensure this header is included to use wys::basic_string

typedef void (*EntryFunction)(const wys::basic_string<char>&);
typedef void (*LoopFunction)();

int main(int argc, char *const argv[])
{
  if (argc < 2)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Expected input file\n";
    return 1;
  }

  HMODULE hModule = LoadLibraryA(argv[1]);
  if (!hModule)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Could not load the DLL" << std::endl;
    return 1;
  }

  // Define the entry function type to include the string argument
  EntryFunction entryFunc = (EntryFunction)GetProcAddress(hModule, "_entry");
  if (!entryFunc)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Could not find the entry function" << std::endl;
    FreeLibrary(hModule);
    return 1;
  }

  // Create a wys::string to pass as an argument
  wys::basic_string<char> arg;
  
  for (int i = 1; i < argc; ++i)
  {
    arg += argv[i];
    arg += " ";
  }

  // Call the entry function with the wys::string argument
  entryFunc(arg);

  // Get and call the loop function if it exists
  LoopFunction loopFunc = (LoopFunction)GetProcAddress(hModule, "_loop");
  if (loopFunc)
  {
    loopFunc();
  }

  FreeLibrary(hModule);

  return 0;
}
