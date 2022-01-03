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

std::string AVAILABLE_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

int index(char c) {
	for (int ii = 0; ii < AVAILABLE_CHARS.size(); ii++) {
		if (AVAILABLE_CHARS[ii] == c) {
			return ii;
		}
	}
	return -1;
}


std::string extend_key(std::string& msg, std::string& key) {
	int msgLen = msg.size();
	std::string newKey(msgLen, 'x');
	int keyLen = key.size(), i, j;
	for (i = 0, j = 0; i < msgLen; ++i, ++j) {
		if (j == keyLen)
			j = 0;

		newKey[i] = key[j];
	}
	newKey[i] = '\0';
	return newKey;
}


std::string encrypt_vigenere(std::string& msg, std::string& key) {
	int msgLen = msg.size(), keyLen = key.size(), i, j;
	std::string encryptedMsg(msgLen, 'x');
	// char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];

	std::string newKey = extend_key(msg, key);

	//encryption
	for (i = 0; i < msgLen; ++i) {
		// std::cout << msg[i] << " " << isalnum(msg[i]) << std::endl;
		if (isalnum(msg[i]) or msg[i] == ' ') {
			encryptedMsg[i] = AVAILABLE_CHARS[((index(msg[i]) + index(newKey[i])) % AVAILABLE_CHARS.size())];
		}
		else {
			encryptedMsg[i] = msg[i];
		}
	}

	encryptedMsg[i] = '\0';
	return encryptedMsg;
}

std::string decrypt_vigenere(std::string& encryptedMsg, std::string& newKey) {
	// decryption
	int msgLen = encryptedMsg.size();
	std::string decryptedMsg(msgLen, 'x');
	int i;
	for (i = 0; i < msgLen; ++i) {
		if (isalnum(encryptedMsg[i]) or encryptedMsg[i] == ' ') {
			decryptedMsg[i] = AVAILABLE_CHARS[(((index(encryptedMsg[i]) - index(newKey[i])) + AVAILABLE_CHARS.size()) % AVAILABLE_CHARS.size())];
		}
		else {
			decryptedMsg[i] = encryptedMsg[i];
		}
	}
	decryptedMsg[i] = '\0';
	return decryptedMsg;
}


//EXP:
// 	string encryption_sentence;
//string new_key;
//string unencryption_sentence;
//? string test_encryption = "this write you want need encryption data";
//string test_key = "WnCry236";
//x encryption_sentence = encrypt_vigenere(test_encryption, test_key);   encryptioning.......
//cout << encryption_sentence << endl;
//!? new_key = extend_key(encryption_sentence, test_key);
//cout << new_key << endl;
//! unencryption_sentence = decrypt_vigenere(encryption_sentence, new_key);
//cout << unencryption_sentence << endl;