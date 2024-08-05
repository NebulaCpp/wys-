#include <iostream>
#include <windows.h>

typedef void (*EntryFunction)();
typedef void (*LoopFunction)();

int main(int argc, char *const argv[])
{
  if (argc < 2)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Expected input file\n";
  }

  HMODULE hModule = LoadLibraryA(argv[1]);
  if (!hModule)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Could not load the DLL" << std::endl;
    return 1;
  }


  EntryFunction entryFunc = (EntryFunction)GetProcAddress(hModule, "_entry");
  if (!entryFunc)
  {
    std::cerr << "[wys]: > Wys! <loader>: <error>: Could not find the entry function" << std::endl;
    FreeLibrary(hModule);
    return 1;
  }

  entryFunc();

  LoopFunction loopFunc = (LoopFunction)GetProcAddress(hModule, "_loop");
  if (loopFunc)
  {
    loopFunc();
  }

  FreeLibrary(hModule);

  return 0;
}

/*



*/