#include "Un-main.h"
#include"resource/Encryption/aes_pre.h"
using namespace std;
const char* buff = ".WaotoCry";


/*
全局变量区
*/





int Encryption(char process_path) {
	int i;
	int cnt;//计数，每16字符一组
	char PP;//读取明文(或密文)
	//char Key[32];//密钥字符串--16进制
	int K[4];//密钥word二进制（32位）
	char P[16];//明文(或密文)16字符一组加密，每组8bit.
	char  fin[256], fout[256];//输入输出文件名
	//文件流输入输出
	cin >> fin;//input path
	ifstream infile(fin, ios::in | ios::binary);
	if (!infile) {
		cout << "infile error" << endl;
		cin >> i;
		return 0;
	}
	strcat_s(fin, buff);  //默认保存在同文件夹，后缀.aes
	ofstream outfile(fin, ios::out | ios::binary);
	if (!outfile) {
		cout << "outfile error" << endl;
		infile.close();
		cin >> i;
		return 0;
	}
	infile.unsetf(ios::skipws); //设置为不跳过文件中的空格
	//开始加密
	cnt = 0;//初始值
	while (infile.get(PP)) {  //每次读取一个字符
		P[cnt] = PP;//明文转换为 二进制
		cnt += 1;
		if (cnt == 16) {  //每八个一组
			cnt = 0; //clear
			aes(P, K);//加密
			for (i = 0; i < 16; i++) {
				outfile.put(P[i]);  //每次写入一个字符
			}
		}
	}
	if (cnt != 0) {  //文件非整16字符的倍数
		for (i = cnt; i < 16; i++) {
			P[i] = 0;
		}
		cnt = 0;
		aes(P, K);//加密
		for (i = 0; i < 16; i++) {
			outfile.put(P[i]);  //每次写入一个字符
		}
	}
	outfile.close();
	infile.close();
}
	



