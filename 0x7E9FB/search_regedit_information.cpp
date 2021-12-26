#include  "Un-main.h"
//#include <malloc.h>


//!?  CPU-->HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System\CentralProcessor\0
//? NAEM->ProcessorNameString 的值为CPU型号

WCHAR search_regedit_CPU_information() {
	string cpu_information;
	DWORD dwType = REG_SZ;
	DWORD dwValue = 0;
	DWORD dwSize = sizeof(dwValue);
	WCHAR CPU_information[MAX_PATH];
	char regeditp[] = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	HKEY key;
	//！ 打开注册表
	LONG lResult = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, regeditp, 0, KEY_READ, &key);
	printf("%d\n", lResult);
	//if (lResult != ERROR_SUCCESS)
	//{
	//	if (lResult == ERROR_FILE_NOT_FOUND) {
	//		printf("Key not found.\n");
	//		return TRUE;
	//	}
	//	else {
	//		printf("Error opening key.\n");
	//		return FALSE;
	//	}
	//}
	//! 向注册表查询CPU型号
	printf("%d", ::RegQueryValueEx(key, TEXT("ProcessorNameString"), 0, &dwType, (LPBYTE)CPU_information, &dwSize));
	if (::RegQueryValueEx(key, TEXT("ProcessorNameString"), 0, &dwType, (LPBYTE)CPU_information, &dwSize) == ERROR_SUCCESS)
	{
		//return error_word;
		/*printf("read success\n");
		printf("%s\n", CPU_information);*/
		strcat((char*)cpu_information.c_str(), (char*)CPU_information);
		//cout << "STRING--->" << cpu_information << endl;
		return (WCHAR)CPU_information;
	}
}

//! 查询GPU型号 [需要做遍历查询-->GeForce<--查询这个值后面的值  EXP-->]
//? HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\PCI

char search_regedit_GPU_information() {
	return 0;
}


//? HWID: Usernaem+CPU ID+硬盘ID +BIOS ID

//! search System Username 
string search_System_username() {
	char username[256];
	DWORD dwusernaem[256] = {0};
	GetUserNameA((LPSTR)username, (LPDWORD)&dwusernaem);
	return username;
}

