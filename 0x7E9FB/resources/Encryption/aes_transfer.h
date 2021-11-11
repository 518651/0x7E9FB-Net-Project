/*
开发者：晓鸩 
开发时间：2020年
参考博文：https://blog.csdn.net/qq_28205153/article/details/55798628 
*/
#include<iostream>
#include<cstring> 

/***********************函数声明**********************************************************/
static int getIntFromChar(char c);//字符转整型
static int getWordFromStr(char str[4]);//把连续的4个字符合并成一个4字节的整型
static int mergeArrayToInt(int array[4]) ;// 把数组中的第一、二、三和四元素分别作为    4字节整型的第一、二、三和四字节，合并成一个4字节整型
static void convertToIntArray(char str[16], int pa[4][4]);//把16个字符转变成4X4的数组,用于明文输入
static void splitIntToArray(int num, int array[4]);//把一个4字节的数的第一、二、三、四个字节取出， 放入一个4个元素的整型数组里面。
static int getLeft4Bit(int num);//获取整形数据的低8位的左4个位
static int getRight4Bit(int num);//获取整形数据的低8位的右4个位 
static void leftLoop4int(int array[4], int step);//将数组中的元素循环左移step位
static void rightLoop4int(int array[4], int step);// 把4个元素的数组循环右移step位
static int GFMul(int n, int s);//GF上的二元运算
static void convertArrayToStr(int array[4][4], char str[16]);//把4X4数组转回字符串
static void addRoundTowArray(int aArray[4][4],int bArray[4][4]);//把两个4X4数组进行异或
/************************************************************************************************************/

/**
 * 把一个字符转变成整型
 */
static int getIntFromChar(char c) {
	int result = (int) c;
	return result & 0x000000ff;
}

/**
 * 把连续的4个字符合并成一个4字节的整型
 */
static int getWordFromStr(char str[4]) {
	int one, two, three, four;
	one = getIntFromChar(str[0]);
	one = one << 24;
	two = getIntFromChar(str[1]);
	two = two << 16;
	three = getIntFromChar(str[2]);
	three = three << 8;
	four = getIntFromChar(str[3]);
	return one | two | three | four;
}
/**
 * 把数组中的第一、二、三和四元素分别作为
 * 4字节整型的第一、二、三和四字节，合并成一个4字节整型
 */
static int mergeArrayToInt(int array[4]) {
	int one = array[0] << 24;
	int two = array[1] << 16;
	int three = array[2] << 8;
	int four = array[3];
	return one | two | three | four;
}
/**
 * 把16个字符转变成4X4的数组，
 * 该矩阵中字节的排列顺序为从上到下，
 * 从左到右依次排列。
 */
static void convertToIntArray(char str[16], int pa[4][4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			pa[j][i] = getIntFromChar(str[4*i+j]);
		}
}
/**
 * 把一个4字节的数的第一、二、三、四个字节取出，
 * 入进一个4个元素的整型数组里面。
 */
static void splitIntToArray(int num, int array[4]) {
	int one, two, three;
	one = num >> 24;
	array[0] = one & 0x000000ff;
	two = num >> 16;
	array[1] = two & 0x000000ff;
	three = num >> 8;
	array[2] = three & 0x000000ff;
	array[3] = num & 0x000000ff;
}
/**
 * 获取整形数据的低8位的左4个位
 */
static int getLeft4Bit(int num) {
	int left = num & 0x000000f0;
	return left >> 4;
}

/**
 * 获取整形数据的低8位的右4个位
 */
static int getRight4Bit(int num) {
	return num & 0x0000000f;
}
/**
 * 将数组中的元素循环左移step位
 */
static void leftLoop4int(int array[4], int step) {
	int temp[4];
	int i;
	int index;
	for(i = 0; i < 4; i++)
		temp[i] = array[i];

	index = step % 4 == 0 ? 0 : step % 4;
	for(i = 0; i < 4; i++){
		array[i] = temp[index];
		index++;
		index = index % 4;
	}
}
/**
 * 把4个元素的数组循环右移step位
 */
static void rightLoop4int(int array[4], int step) {
	int temp[4];
	int i;
	int index;
	for(i = 0; i < 4; i++)
		temp[i] = array[i];

	index = step % 4 == 0 ? 0 : step % 4;
	index = 3 - index;
	for(i = 3; i >= 0; i--) {
		array[i] = temp[index];
		index--;
		index = index == -1 ? 3 : index;
	}
}
//GF域上列混淆运算
static int GFMul2(int s) {
	int result = s << 1;
	int a7 = result & 0x00000100;

	if(a7 != 0) {
		result = result & 0x000000ff;
		result = result ^ 0x1b;
	}

	return result;
}

static int GFMul3(int s) {
	return GFMul2(s) ^ s;
}

static int GFMul4(int s) {
	return GFMul2(GFMul2(s));
}

static int GFMul8(int s) {
	return GFMul2(GFMul4(s));
}

static int GFMul9(int s) {
	return GFMul8(s) ^ s;
}

static int GFMul11(int s) {
	return GFMul9(s) ^ GFMul2(s);
}

static int GFMul12(int s) {
	return GFMul8(s) ^ GFMul4(s);
}

static int GFMul13(int s) {
	return GFMul12(s) ^ s;
}

static int GFMul14(int s) {
	return GFMul12(s) ^ GFMul2(s);
}

/**
 * GF上的二元运算
 */
static int GFMul(int n, int s) {
	int result;

	if(n == 1)
		result = s;
	else if(n == 2)
		result = GFMul2(s);
	else if(n == 3)
		result = GFMul3(s);
	else if(n == 0x9)
		result = GFMul9(s);
	else if(n == 0xb)//11
		result = GFMul11(s);
	else if(n == 0xd)//13
		result = GFMul13(s);
	else if(n == 0xe)//14
		result = GFMul14(s);

	return result;
}
/**
 * 把4X4数组转回字符串-16字符
 */
static void convertArrayToStr(int array[4][4], char str[16]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			str[4*i+j]= (char)array[j][i];
}
/**
 * 把两个4X4数组进行异或
 */
static void addRoundTowArray(int aArray[4][4],int bArray[4][4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}
