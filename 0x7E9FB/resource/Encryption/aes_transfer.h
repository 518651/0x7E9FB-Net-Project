/*
�����ߣ���� 
����ʱ�䣺2020��
�ο����ģ�https://blog.csdn.net/qq_28205153/article/details/55798628 
*/
#include<iostream>
#include<cstring> 

/***********************��������**********************************************************/
static int getIntFromChar(char c);//�ַ�ת����
static int getWordFromStr(char str[4]);//��������4���ַ��ϲ���һ��4�ֽڵ�����
static int mergeArrayToInt(int array[4]) ;// �������еĵ�һ������������Ԫ�طֱ���Ϊ    4�ֽ����͵ĵ�һ�������������ֽڣ��ϲ���һ��4�ֽ�����
static void convertToIntArray(char str[16], int pa[4][4]);//��16���ַ�ת���4X4������,������������
static void splitIntToArray(int num, int array[4]);//��һ��4�ֽڵ����ĵ�һ�����������ĸ��ֽ�ȡ���� ����һ��4��Ԫ�ص������������档
static int getLeft4Bit(int num);//��ȡ�������ݵĵ�8λ����4��λ
static int getRight4Bit(int num);//��ȡ�������ݵĵ�8λ����4��λ 
static void leftLoop4int(int array[4], int step);//�������е�Ԫ��ѭ������stepλ
static void rightLoop4int(int array[4], int step);// ��4��Ԫ�ص�����ѭ������stepλ
static int GFMul(int n, int s);//GF�ϵĶ�Ԫ����
static void convertArrayToStr(int array[4][4], char str[16]);//��4X4����ת���ַ���
static void addRoundTowArray(int aArray[4][4],int bArray[4][4]);//������4X4����������
/************************************************************************************************************/

/**
 * ��һ���ַ�ת�������
 */
static int getIntFromChar(char c) {
	int result = (int) c;
	return result & 0x000000ff;
}

/**
 * ��������4���ַ��ϲ���һ��4�ֽڵ�����
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
 * �������еĵ�һ������������Ԫ�طֱ���Ϊ
 * 4�ֽ����͵ĵ�һ�������������ֽڣ��ϲ���һ��4�ֽ�����
 */
static int mergeArrayToInt(int array[4]) {
	int one = array[0] << 24;
	int two = array[1] << 16;
	int three = array[2] << 8;
	int four = array[3];
	return one | two | three | four;
}
/**
 * ��16���ַ�ת���4X4�����飬
 * �þ������ֽڵ�����˳��Ϊ���ϵ��£�
 * �������������С�
 */
static void convertToIntArray(char str[16], int pa[4][4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			pa[j][i] = getIntFromChar(str[4*i+j]);
		}
}
/**
 * ��һ��4�ֽڵ����ĵ�һ�����������ĸ��ֽ�ȡ����
 * ���һ��4��Ԫ�ص������������档
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
 * ��ȡ�������ݵĵ�8λ����4��λ
 */
static int getLeft4Bit(int num) {
	int left = num & 0x000000f0;
	return left >> 4;
}

/**
 * ��ȡ�������ݵĵ�8λ����4��λ
 */
static int getRight4Bit(int num) {
	return num & 0x0000000f;
}
/**
 * �������е�Ԫ��ѭ������stepλ
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
 * ��4��Ԫ�ص�����ѭ������stepλ
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
//GF�����л�������
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
 * GF�ϵĶ�Ԫ����
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
 * ��4X4����ת���ַ���-16�ַ�
 */
static void convertArrayToStr(int array[4][4], char str[16]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			str[4*i+j]= (char)array[j][i];
}
/**
 * ������4X4����������
 */
static void addRoundTowArray(int aArray[4][4],int bArray[4][4]) {
	int i,j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}
