#include "Un-main.h"
#include"resource/Encryption/aes_pre.h"
using namespace std;
const char* buff = ".WaotoCry";


/*
ȫ�ֱ�����
*/





int Encryption(char process_path) {
	int i;
	int cnt;//������ÿ16�ַ�һ��
	char PP;//��ȡ����(������)
	//char Key[32];//��Կ�ַ���--16����
	int K[4];//��Կword�����ƣ�32λ��
	char P[16];//����(������)16�ַ�һ����ܣ�ÿ��8bit.
	char  fin[256], fout[256];//��������ļ���
	//�ļ����������
	cin >> fin;//input path
	ifstream infile(fin, ios::in | ios::binary);
	if (!infile) {
		cout << "infile error" << endl;
		cin >> i;
		return 0;
	}
	strcat_s(fin, buff);  //Ĭ�ϱ�����ͬ�ļ��У���׺.aes
	ofstream outfile(fin, ios::out | ios::binary);
	if (!outfile) {
		cout << "outfile error" << endl;
		infile.close();
		cin >> i;
		return 0;
	}
	infile.unsetf(ios::skipws); //����Ϊ�������ļ��еĿո�
	//��ʼ����
	cnt = 0;//��ʼֵ
	while (infile.get(PP)) {  //ÿ�ζ�ȡһ���ַ�
		P[cnt] = PP;//����ת��Ϊ ������
		cnt += 1;
		if (cnt == 16) {  //ÿ�˸�һ��
			cnt = 0; //clear
			aes(P, K);//����
			for (i = 0; i < 16; i++) {
				outfile.put(P[i]);  //ÿ��д��һ���ַ�
			}
		}
	}
	if (cnt != 0) {  //�ļ�����16�ַ��ı���
		for (i = cnt; i < 16; i++) {
			P[i] = 0;
		}
		cnt = 0;
		aes(P, K);//����
		for (i = 0; i < 16; i++) {
			outfile.put(P[i]);  //ÿ��д��һ���ַ�
		}
	}
	outfile.close();
	infile.close();
}
	



