#include "Un-main.h"



bool CreateMyFile(char* strFilePath, LPBYTE lpBuffer, DWORD dwSize)
{
	DWORD dwWritten;

	HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile != NULL)
	{
		WriteFile(hFile, (LPCVOID)lpBuffer, dwSize, &dwWritten, NULL);
	}
	else
	{
		return false;
	}
	CloseHandle(hFile);
	return true;
}

bool CreateEXE(char* strFilePath, int nResourceID, char* strResourceName)
{
	//strcat(strFilePath, "\\libuv.dll");
	//cout << "ÊÍ·ÅÂ·¾¶" << strFilePath << endl;
	HRSRC hResInfo;
	HGLOBAL hResData;
	DWORD dwSize;
	LPBYTE p;
	hResInfo = FindResource(NULL, MAKEINTRESOURCE(nResourceID), strResourceName);
	if (hResInfo == NULL)
	{
		//MessageBox(NULL, "²éÕÒ×ÊÔ´Ê§°Ü£¡", "´íÎó", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	dwSize = SizeofResource(NULL, hResInfo);
	hResData = LoadResource(NULL, hResInfo);
	if (hResData == NULL)
	{
		//MessageBox(NULL, "×°ÔØ×ÊÔ´Ê§°Ü£¡","´íÎó", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	p = (LPBYTE)GlobalAlloc(GPTR, dwSize);
	if (p == NULL)
	{
		//MessageBox(NULL, "·ÖÅäÄÚ´æÊ§°Ü£¡", "´íÎó", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	CopyMemory((LPVOID)p, (LPCVOID)LockResource(hResData), dwSize);

	bool bRet = CreateMyFile(strFilePath, p, dwSize);
	if (!bRet)
	{
		GlobalFree((HGLOBAL)p);
		return false;
	}

	GlobalFree((HGLOBAL)p);

	return true;
}


BOOL ReleaseDLLRes(LPCTSTR szDLLFullPath, UINT uResID, LPCTSTR szResType)
{
	if (uResID <= 0 || !szResType)
	{
		return FALSE;
	}

	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(uResID), szResType);
	if (NULL == hRsrc)
	{
		return FALSE;
	}

	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (dwSize <= 0)
	{
		return FALSE;
	}

	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		return FALSE;
	}

	LPVOID pBuffer = LockResource(hGlobal);
	if (NULL == pBuffer)
	{
		return FALSE;
	}

	HANDLE hFile = CreateFile(szDLLFullPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}


	DWORD dwWrited = 0;
	if (FALSE == WriteFile(hFile, pBuffer, dwSize, &dwWrited, NULL))
	{
		return FALSE;
	}

	CloseHandle(hFile);
	UnlockResource(hGlobal);
	FreeResource(hGlobal);
	return TRUE;
}





