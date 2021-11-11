/*
开发者：晓鸩 
开发时间：2020年 
https://blog.csdn.net/qq_28205153/article/details/55798628
*/
#include<iostream>
#include<cstring> 
#include"aes_transfer.h"
using namespace std;
const int length = 32;
/**
 * S盒
 */
static const int S[16][16] = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

/**
 * 逆S盒
 */
static const int S2[16][16] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
/**
 * 密钥扩展常量轮值表
 */
static const int Rcon[10] = { 0x01000000, 0x02000000,
	0x04000000, 0x08000000,
	0x10000000, 0x20000000,
	0x40000000, 0x80000000,
	0x1b000000, 0x36000000 };
/**
 * 列混合要用到的矩阵
 */
static const int colM[4][4] = { 2, 3, 1, 1,
	1, 2, 3, 1,
	1, 1, 2, 3,
	3, 1, 1, 2 };
/**
 * 逆列混合用到的矩阵
 */
static const int deColM[4][4] = { 0xe, 0xb, 0xd, 0x9,
	0x9, 0xe, 0xb, 0xd,
	0xd, 0x9, 0xe, 0xb,
	0xb, 0xd, 0x9, 0xe };

/***********************函数声明**********************************************************/
int key_turn(int K[4]);//读入密钥字符串，转化为4个二进制word（32bit）

void aes(char p[16], char Key[32]);//AES加密
void deAes(char c[16], int K[4]);//AES解密

static void extendKey(int K[4]);//扩展密钥，结果是把w[44]中的每个元素初始化
static void getArrayFrom4W(int i, int array[4][4]);//从4个32位的密钥字中获得4X4数组,用于进行逆列混合

static void addRoundKey(int array[4][4], int round);//轮密钥加

static int getNumFromSBox(int index);//根据索引，从S盒中获得元素
static int getNumFromS1Box(int index);//根据索引从逆S盒中获取值

static void subBytes(int array[4][4]);//字节代换
static void deSubBytes(int array[4][4]);//逆字节代换

static void shiftRows(int array[4][4]);//行移位
static void deShiftRows(int array[4][4]);//逆行移位

static void mixColumns(int array[4][4]);//列混合
static void deMixColumns(int array[4][4]);//逆列混合

static int T(int num, int round);//密钥扩展中的T函数

/************************************************************************************************************/

/*
密钥输入读取转换
*/
int key_turn(int K[4]){    //密钥转化字符串转化为二进制byte ****************************************************** 
	int i,j;
	int kb=0;
	int tmp=0;
	char Key[100];//暂存密钥
	cout<<"**************请输入16进制密钥，共32位，以回车结尾,若非16进制，则按0处理；超过取前32位**************"<<endl;  //若数据超过 则截取 
	cin.getline(Key,100); //包含结尾/0字符 
	for(i=0;i<4;i++){   //密钥转二进制
		for(j=0;j<8;j++){
			kb=kb<<4;//左移四位，每位字符代表4bit密钥
			switch(Key[8*i+j]){
			case'0':tmp=0x0;break;
			case'1':tmp=0x1;break;
			case'2':tmp=0x2;break;
			case'3':tmp=0x3;break;
			case'4':tmp=0x4;break;
			case'5':tmp=0x5;break;
			case'6':tmp=0x6;break;
			case'7':tmp=0x7;;break;
			case'8':tmp=0x8;break;
			case'9':tmp=0x9;break;
			case'a':case'A':tmp=0xa;break;
			case'b':case'B':tmp=0xb;break;
			case'c':case'C':tmp=0xc;break;
			case'd':case'D':tmp=0xd;break;
			case'e':case'E':tmp=0xe;break;
			case'f':case'F':tmp=0xf;break;
			default:tmp=0x0;       //若非16进制 则按0处理 
			}
			kb+=tmp;//追加密钥
		}
		K[i]=kb;	//赋值输出
		kb=0;//清零
	}
	cout<<"*************************************************"<<endl; 
	cout<<"***************十六进制密钥为：********************"<<endl; 
	for(i=0;i<4;i++){
		cout.fill('0');//补位0
		cout.width(8);//设置位宽为8byte
		cout<<hex<<K[i]<<" ";//十六进制显示
	}
	cout<<"*************************************************"<<endl; 
	cout<<endl;
	return 0;
} 

/**
 * 密钥扩展中的T函数
 */
static int T(int num, int round) {
	int numArray[4];
	int i;
	int result;
	splitIntToArray(num, numArray);
	leftLoop4int(numArray, 1);//字循环

	//字节代换
	for(i = 0; i < 4; i++)
		numArray[i] = getNumFromSBox(numArray[i]);

	result = mergeArrayToInt(numArray);
	return result ^ Rcon[round];
}
/**
 * 扩展密钥，结果是把w[44]中的每个元素初始化
 */
static int w[44];//每个元素4byte
static void extendKey(int K[4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		w[i] = K[i];
	for(i = 4, j = 0; i < 44; i++) {
		if( i % 4 == 0) {
			w[i] = w[i - 4] ^ T(w[i - 1], j);
			j++;//下一轮
		}else {
			w[i] = w[i - 4] ^ w[i - 1];
		}
	}
}
/**
 * 根据索引，从S盒中获得元素
 */
static int getNumFromSBox(int index) {
	int row = getLeft4Bit(index);
	int col = getRight4Bit(index);
	return S[row][col];
}
/**
 * 根据索引从逆S盒中获取值
 */
static int getNumFromS1Box(int index) {
	int row = getLeft4Bit(index);
	int col = getRight4Bit(index);
	return S2[row][col];
}
/**
 * 轮密钥加
 */
static void addRoundKey(int array[4][4], int round) {
	int warray[4];
	int i,j;
	for(i = 0; i < 4; i++) {

		splitIntToArray(w[ round * 4 + i], warray);

		for(j = 0; j < 4; j++) {
			array[j][i] = array[j][i] ^ warray[j];
		}
	}
}

/**
 * 字节代换
 */
static void subBytes(int array[4][4]){
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			array[i][j] = getNumFromSBox(array[i][j]);
}
/**
 * 逆字节变换
 */
static void deSubBytes(int array[4][4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			array[i][j] = getNumFromS1Box(array[i][j]);
}
/**
 * 行移位
 */
static void shiftRows(int array[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	int i;
	for(i = 0; i < 4; i++) {
		rowTwo[i] = array[1][i];
		rowThree[i] = array[2][i];
		rowFour[i] = array[3][i];
	}

	leftLoop4int(rowTwo, 1);
	leftLoop4int(rowThree, 2);
	leftLoop4int(rowFour, 3);

	for(i = 0; i < 4; i++) {
		array[1][i] = rowTwo[i];
		array[2][i] = rowThree[i];
		array[3][i] = rowFour[i];
	}
}
/**
 * 逆行移位
 */
static void deShiftRows(int array[4][4]) {
	int rowTwo[4], rowThree[4], rowFour[4];
	int i;
	for(i = 0; i < 4; i++) {
		rowTwo[i] = array[1][i];
		rowThree[i] = array[2][i];
		rowFour[i] = array[3][i];
	}

	rightLoop4int(rowTwo, 1);
	rightLoop4int(rowThree, 2);
	rightLoop4int(rowFour, 3);

	for(i = 0; i < 4; i++) {
		array[1][i] = rowTwo[i];
		array[2][i] = rowThree[i];
		array[3][i] = rowFour[i];
	}
}
/**
 * 列混合
 */
static void mixColumns(int array[4][4]) {

	int tempArray[4][4];
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			tempArray[i][j] = array[i][j];

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++){
			array[i][j] = GFMul(colM[i][0],tempArray[0][j]) ^ GFMul(colM[i][1],tempArray[1][j])
				^ GFMul(colM[i][2],tempArray[2][j]) ^ GFMul(colM[i][3], tempArray[3][j]);
		}
}
/**
 * 逆列混合
 */
static void deMixColumns(int array[4][4]) {
	int tempArray[4][4];
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			tempArray[i][j] = array[i][j];

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++){
			array[i][j] = GFMul(deColM[i][0],tempArray[0][j]) ^ GFMul(deColM[i][1],tempArray[1][j])
				^ GFMul(deColM[i][2],tempArray[2][j]) ^ GFMul(deColM[i][3], tempArray[3][j]);
		}
}
/**
 * 从4个32位的密钥字中获得4X4数组，
 * 用于进行逆列混合
 */
static void getArrayFrom4W(int i, int array[4][4]) {
	int index,j;
	int colOne[4], colTwo[4], colThree[4], colFour[4];
	index = i * 4;
	splitIntToArray(w[index], colOne);
	splitIntToArray(w[index + 1], colTwo);
	splitIntToArray(w[index + 2], colThree);
	splitIntToArray(w[index + 3], colFour);

	for(j = 0; j < 4; j++) {
		array[j][0] = colOne[j];
		array[j][1] = colTwo[j];
		array[j][2] = colThree[j];
		array[j][3] = colFour[j];
	}
}
/**
 * 参数 p: 明文的字符串数组--16字符。
 * 参数 key: 密钥的字符串数组。
 */
void aes(char p[16], int K[4]){
	int pArray[4][4];//明文矩阵
	int i;
	extendKey(K);//扩展密钥
	convertToIntArray(p, pArray);//明文转二维数组

	addRoundKey(pArray, 0);//一开始的轮密钥加--第一轮
	for(i = 1; i < 10; i++){//前九轮

		subBytes(pArray);//字节代换
		shiftRows(pArray);//行移位
		mixColumns(pArray);//列混合
		addRoundKey(pArray, i);//轮密钥加

	}
	//第十轮
	subBytes(pArray);//字节代换
	shiftRows(pArray);//行移位
	addRoundKey(pArray, 10);//轮密钥加
	convertArrayToStr(pArray, p);//二维数组转明文
}
/**
 * 参数 c: 密文的字符串数组。
 * 参数 clen: 密文的长度。
 * 参数 key: 密钥的字符串数组。
 */
void deAes(char c[16], int K[4]) {
	int cArray[4][4];//密文矩阵
	int i;
	int wArray[4][4];//逆列混合矩阵

	extendKey(K);//扩展密钥
	convertToIntArray(c, cArray);//密文转二维数组

	addRoundKey(cArray, 10);//逆序执行，第十轮

	for(i = 9; i >= 1; i--) {  //第九轮到第一轮
		deSubBytes(cArray);//字节代换

		deShiftRows(cArray);//行移位

		deMixColumns(cArray);//列混合
		getArrayFrom4W(i, wArray);//轮密钥加
		deMixColumns(wArray);

		addRoundTowArray(cArray, wArray);
	}
	//第1轮
	deSubBytes(cArray); 

	deShiftRows(cArray);

	addRoundKey(cArray, 0);

	convertArrayToStr(cArray, c);
}
