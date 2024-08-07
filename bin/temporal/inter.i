include Windows.h

function printfmt(fmt: vector<string>)(void):
  for (size_t i = 0; i < fmt.size(); ++i):
    printf(fmt[i])
  end
end

function get_time()(float):
  var st: SYSTEMTIME = {} // null initialisation
  GetSystemTime(&st)

  var time: float = st.wHour * 10000.0f + st.wMinute * 100.0f + st.wSecond + st.wMilliseconds / 1000.0f
  return time
end

function get_exe_dir()(string):
  var path: char[MAX_PATH] = {}
  GetModuleFileNameA(NULL, path, MAX_PATH)
  var fullPath: string = string(path)
  return fullPath
end


function optimize_memory()(void):
  var processes: DWORD[1024] = {}
  var cbNeeded: DWORD = 0
  var cProcesses: DWORD = 0
  var i: unsigned int = 0

  if (not EnumProcesses(processes, sizeof(processes), &cbNeeded)):
    printf("WysAPI: Error: Failed to enumerate processes.")
    return
  end
  
  cProcesses = cbNeeded / sizeof(DWORD)

  for (int i = 0; i < cProcesses; i++):
    if (processes[i] != 0):
      var hProcess: HANDLE = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_SET_QUOTA, FALSE, processes[i])
      if (hProcess != NULL):
        var processName: TCHAR[MAX_PATH] = {}

        var hMod: HMODULE = NULL
        var cbNeededMod: DWORD = 0
        if EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeededMod):
          GetModuleBaseName(hProcess, hMod, processName, sizeof(processName) / sizeof(TCHAR))
          printfmt({string("Optimizing memory for process: "), string(processName), string(" (PID: "), string(processes[i]), string(")\n")})        

        if (not SetProcessWorkingSetSize(hProcess, -1, -1)):
          printfmt({"WysAPI: Error: Failed to optimize memory for process: ", string(aProcesses[i])})
        end

        CloseHandle(hProcess)
      end 
    end 
  end 
end
