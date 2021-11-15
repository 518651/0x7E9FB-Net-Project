#include "Un-main.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <tchar.h>

DWORD get_parent_processid(DWORD pid)
{
	DWORD ParentProcessID = -1;

	PROCESSENTRY32 pe;

	HANDLE hkz;

	HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));

	FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");

	if (Address == NULL) {
		OutputDebugString(_T("GetProc error"));
		return(-1);
	}

	_asm {
		push 0
		push 2
		call Address
		mov hkz, eax
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hkz, &pe)) {
		do {
			if (pe.th32ProcessID == pid) {
				ParentProcessID = pe.th32ParentProcessID;
				break;
			}
		} while (Process32Next(hkz, &pe));
	}
	return ParentProcessID;
}


DWORD get_explorer_processid() {
	DWORD explorer_id = -1;
	PROCESSENTRY32 pe;
	HANDLE hkz;
	HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));

	if (hModule == NULL) {
		OutputDebugString(_T("Loaddll error"));
		return(-1);
	}
	FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");

	if (Address == NULL) {
		OutputDebugString(_T("GetProc error"));
		return(-1);
	}

	_asm {
		push 0
		push 2
		call Address
		mov hkz, eax
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hkz, &pe)) {
		do {
			if (strcmp((const char*)pe.szExeFile, "explorer.exe") == 0)
			{			
					explorer_id = pe.th32ProcessID;						
					break;
			}
		} while (Process32Next(hkz, &pe));
	}
	return explorer_id;
}




int determine() {
	DWORD explorer_id = get_explorer_processid();
	cout << "explorer_id:" << explorer_id << endl;
	DWORD Parent_id = get_parent_processid(GetCurrentProcessId());
	cout << "Parent_id" << Parent_id <<endl;
	if (explorer_id == Parent_id)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




DWORD GetProcesspId(const char*name)
{
	DWORD process_id = -1;
	PROCESSENTRY32 pe;
	HANDLE hkz;
	HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));

	if (hModule == NULL) {
		OutputDebugString(_T("Loaddll error"));
		return(-1);
	}
	FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");

	if (Address == NULL) {
		OutputDebugString(_T("GetProc error"));
		return(-1);
	}

	_asm {
		push 0
		push 2
		call Address
		mov hkz, eax
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hkz, &pe)) {
		do {
			if (strcmp((const char*)pe.szExeFile, name) == 0)
			{
				process_id = pe.th32ProcessID;
				break;
			}
		} while (Process32Next(hkz, &pe));
	}
	return process_id;
}



string process_pid_to_path(DWORD process_pid) {
	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_pid);
	string Process_path;
	char Filename[1024];
	GetModuleFileNameExA(Process, NULL, (LPSTR)Filename, 1024);

	if (Filename!=NULL)
	{
		Process_path = Filename;
		return Filename;
	}
	else
	{
		return 0;
	}
	CloseHandle(Process);
	
}