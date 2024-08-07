#include "wlerror.hpp"
#include "wlio.hpp"
#include "wlvector.hpp"
#include "wlmemory.hpp"
#include "wlstring.hpp"
#include "wltype.hpp"
#include "wlutiles.hpp"

using namespace wys;
extern "C" {
#include "Windows.h"
	__declspec(dllexport) void  printfmt( vector<string> fmt) {
	for (size_t i = 0; i < fmt.size(); ++i) {
		printf(fmt[i]);
	};
};
__declspec(dllexport) float  get_time() {
 SYSTEMTIME   st =  {} // null initialisation;
GetSystemTime(&st);
 float   time =  st.wHour * 10000.0f + st.wMinute * 100.0f + st.wSecond + st.wMilliseconds / 1000.0f;
return time;
};
__declspec(dllexport) string  get_exe_dir() {
 char[MAX_PATH]   path =  {};
GetModuleFileNameA(NULL, path, MAX_PATH);
 string   fullPath =  string(path);
return fullPath;
};
__declspec(dllexport) void  optimize_memory() {
 DWORD[1024]   processes =  {};
 DWORD   cbNeeded =  0;
 DWORD   cProcesses =  0;
 unsigned int   i =  0;
if ( (not EnumProcesses(processes, sizeof(processes), &cbNeeded))) {
printf("WysAPI: Error: Failed to enumerate processes.");
return;
};
cProcesses = cbNeeded / sizeof(DWORD);
for (int i = 0; i < cProcesses; i++) {
if ( (processes[i] != 0)) {
 HANDLE   hProcess =  OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_SET_QUOTA, FALSE, processes[i]);
if ( (hProcess != NULL)) {
	 TCHAR[MAX_PATH]   processName =  {};
	 HMODULE   hMod =  NULL;
	 DWORD   cbNeededMod =  0;
	if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeededMod)) {
		GetModuleBaseName(hProcess, hMod, processName, sizeof(processName) / sizeof(TCHAR));
		printfmt({string("Optimizing memory for process: "), string(processName), string(" (PID: "), string(processes[i]), string(")\n")})        ;
		if ( (not SetProcessWorkingSetSize(hProcess, -1, -1))) {
			printfmt({"WysAPI: Error: Failed to optimize memory for process: ", string(aProcesses[i])});
		};
		CloseHandle(hProcess);
	};
};
};
};
}