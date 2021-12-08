#include "Un-main.h"
#include"resource/Encryption/aes_pre.h"
using namespace std;
const char* buff = ".WaotoCry";


/*
全局变量区
*/

//AES

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
		cin >> i;
		return 0;
	}
	strcat_s(fin, buff);  //默认保存在同文件夹，后缀.aes
	ofstream outfile(fin, ios::out | ios::binary);
	if (!outfile) {
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
	

//? AES加密数据模块
int Aes_Encryption_Funtion(BYTE* ppassword, DWORD dwpasswordLength, BYTE* pData, DWORD& dwDatalength, DWORD dwBufferLength) {
	int bRet;
	HCRYPTPROV hcryptprov;
	HCRYPTPROV hCrypthash;
	HCRYPTPROV hCryptkey;
	do
	{
		//! 获取CSP句柄
		bRet = ::CryptAcquireContext(&hcryptprov, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}
		//!  获取HASH对象 
		bRet = ::CryptCreateHash(hcryptprov, CALG_MD5, NULL, 0, &hCrypthash);
		if (false == bRet)
		{
			break;
		}
		//! 对密钥进行HASH运算
		bRet = ::CryptHashData(hCrypthash, ppassword, dwpasswordLength, 0);
		if (false == bRet)
		{
			break;
		}
		//! 使用HASH生成密钥
		bRet = ::CryptDeriveKey(hcryptprov, CALG_AES_128, hCrypthash, CRYPT_EXPORTABLE, &hCryptkey);
		if (false == bRet)
		{
			break;
		}
		//!? 加密数据
		bRet = ::CryptEncrypt(hCryptkey, NULL, TRUE, 0, pData, &dwDatalength, dwBufferLength);
		if (FALSE == bRet)
		{
			return 0;
		}

	} while (FALSE);
	return bRet;
}



//? AES解密模块
int AES_decrypt_Funtion(BYTE* pPassword, DWORD dwPasswordlength, BYTE* pData, DWORD& dwDataLength, DWORD dwbufferLength) {
	//! 变量区
	int bRet;
	HCRYPTPROV hCryptProv;
	HCRYPTPROV hCrypthash;
	HCRYPTPROV hCryptKey;
	do
	{
		//! 获取CSP句柄
		bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
		if (FALSE == bRet)
		{
			break;
		}
		//！ 创建HASH对象
		bRet = ::CryptCreateHash(hCryptProv, CALG_MD5, NULL, 0, &hCrypthash);
		if (FALSE == bRet)
		{
			break;
		}
		//!  开始生成加密密钥
		bRet = ::CryptHashData(hCrypthash, pPassword, dwPasswordlength, 0);
		if (FALSE == bRet)
		{
			break;
		}
		//!? 开始解密数据
		bRet = ::CryptDecrypt(hCryptKey, NULL, TRUE, 0, pData, &dwDataLength);
		if (FALSE == bRet)
		{
			break;
		}
	} while (false);
	return bRet;
}

