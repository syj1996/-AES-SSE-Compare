#include<stdio.h>
#include<time.h>

#define lk 128			//秘钥长度 
#define Nk (lk/32)		 
#define Nr (lk/32+6)	//圈数 
#define zt 1			//加解密状态，1位加密，0位解密 

union un{
	unsigned int i;
	unsigned char c[4];
	unsigned short s[2];
};

void pf(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
void KeyExpansion_one(unsigned int *Key,unsigned int *W);
void KeyExpansion_two(unsigned int *Key,unsigned int *W);
void csh_jia(unsigned int *B0,unsigned int *B1,unsigned int *S_BOX0,unsigned int *S_BOX1);		//加密初始化 
void csh_jie(unsigned int *B0,unsigned int *B1,unsigned int *S_BOX0,unsigned int *S_BOX1);		//解密初始化 
void fz(unsigned int *W);																		//解密秘钥反转 
void Performance(int s);																		//速度测试函数，s为测试量 
void Encryption(); 
void Decryption();
