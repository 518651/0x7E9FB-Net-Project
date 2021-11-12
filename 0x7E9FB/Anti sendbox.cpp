#include "Un-main.h"

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
	
	int determine() {
	DWORD explorer_id = get_explorer_processid();
	DWORD Parent_id = get_parent_processid(GetCurrentProcessId());
	if (explorer_id==Parent_id)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hkz, &pe)) {
		do {
			if (_wcsicmp((const wchar_t*)pe.szExeFile, L"explorer.exe") == 0)
			{
				explorer_id = pe.th32ProcessID;
				break;
			}
		} while (Process32Next(hkz, &pe));
	}
	return explorer_id;
}
