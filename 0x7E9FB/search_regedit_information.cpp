#include  "Un-main.h"
//#include <malloc.h>


//!?  CPU-->HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System\CentralProcessor\0
//? NAEM->ProcessorNameString ��ֵΪCPU�ͺ�

WCHAR search_regedit_CPU_information() {
	string cpu_information;
	DWORD dwType = REG_SZ;
	DWORD dwValue = 0;
	DWORD dwSize = sizeof(dwValue);
	WCHAR CPU_information[MAX_PATH];
	char regeditp[] = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	HKEY key;
	//�� ��ע���
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
	//! ��ע����ѯCPU�ͺ�
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

//! ��ѯGPU�ͺ� [��Ҫ��������ѯ-->GeForce<--��ѯ���ֵ�����ֵ  EXP-->]
//? HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\PCI

char search_regedit_GPU_information() {
	return 0;
}


//? HWID: Usernaem+CPU ID+Ӳ��ID +BIOS ID

//! search System Username 
string search_System_username() {
	char username[256];
	DWORD dwusernaem[256] = {0};
	GetUserNameA((LPSTR)username, (LPDWORD)&dwusernaem);
	return username;
}

