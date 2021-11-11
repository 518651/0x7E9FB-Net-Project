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


