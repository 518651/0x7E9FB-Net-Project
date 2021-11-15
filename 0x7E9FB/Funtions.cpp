#include "Un-main.h"
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


char new_process_path() {
	string path = _pgmptr;
	char new_process = (char)path.c_str();
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
		printf("%s\n", buffer);
		return buffer;
	}
}



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