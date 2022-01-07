#include "Un-main.h"
#include <TlHelp32.h>

bool file_exists(const wchar_t* name)
{
	std::ifstream infile{ name };
	return infile.good();
}

bool process_exists(const wchar_t* name, uint32_t& pid) {
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		return false;
	auto entry = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	if (Process32First(snapshot,&entry))
	{
		do
		{
			if (!wcscmp((const wchar_t*)entry.szExeFile,name)) {
				pid = entry.th32ParentProcessID;
				CloseHandle(snapshot);
				return true;
			}
		} while (Process32Next(snapshot,&entry));
	}
	CloseHandle(snapshot);
	return false;
}


bool enble_debug_privilege(HANDLE process) {
	LUID luid;
	HANDLE token;
	TOKEN_PRIVILEGES newPrivileges;
	if (!OpenProcessToken(process,TOKEN_ADJUST_PRIVILEGES,&token))
	{
		return false;
	}
	if (!LookupPrivilegeValue(nullptr,SE_DEBUG_NAME,&luid))
	{
		return false;
	}
	newPrivileges.PrivilegeCount = 1;
	newPrivileges.Privileges[0].Luid = luid;
	newPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	return AdjustTokenPrivileges(
		token,
		FALSE,
		&newPrivileges,
		sizeof(newPrivileges),
		nullptr,
		nullptr
	);
}

bool process_open(uint32_t pid, HANDLE& handle) {
	handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD, FALSE, pid);
	return handle != nullptr;
}


bool inject(HANDLE process, const wchar_t* dll)
{
	auto thread = HANDLE{ nullptr };
	auto exit_code = 0;
	auto dllpath = VirtualAllocEx(process, nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	auto success = WriteProcessMemory(process, dllpath, dll, (wcslen(dll) + 1) * sizeof(wchar_t), nullptr);

	if (!dllpath)
		goto fail;

	

	if (!success)
		goto fail;

	thread = CreateRemoteThread(process, nullptr, 0,
		(LPTHREAD_START_ROUTINE)LoadLibraryW, dllpath, 0, nullptr);

	if (!thread) {
		goto fail;
	}

	if (WaitForSingleObject(thread, 4000) == WAIT_OBJECT_0) {
		exit_code = 0;
		GetExitCodeThread(thread, (DWORD*)&exit_code);
	}

fail:
	if (thread)
		CloseHandle(thread);
	if (dllpath)
		VirtualFreeEx(process, dllpath, 0, MEM_RELEASE);

	return exit_code != 0;
}


int inject_to_cS_game() {
	constexpr auto TARGET_FILE = L"lFcGdB.dll";
	constexpr auto TARGET_PROCESS = L"csgo.exe";
	wchar_t fullpath[MAX_PATH] = { 0 };
	auto proc_id = 0u;
	auto proc_handle = HANDLE{ nullptr };
	enble_debug_privilege(GetCurrentProcess());

	try
	{
		if (!file_exists(TARGET_FILE))
			throw runtime_error{ "DLL NOT FOUND" };

		if (!process_exists(TARGET_PROCESS, proc_id))
			throw runtime_error{ "Process is not running" };

		if (!process_open(proc_id,proc_handle))
		{
			throw runtime_error{"Failed to open process"};
		}

		_wfullpath(fullpath, TARGET_FILE, MAX_PATH);

		if (!inject(proc_handle,fullpath))
		{
			throw runtime_error{ "Failed to inject DLL" };
		}
	}
	catch (const std::exception&ex)
	{
		cout << "[ERROR] " << ex.what() << '\n';
		cout << "Press any key to exit..." << '\n';
		cin.get();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}