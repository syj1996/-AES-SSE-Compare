#include<stdio.h>
#include<time.h>

#define lk 128			//��Կ���� 
#define Nk (lk/32)		 
#define Nr (lk/32+6)	//Ȧ�� 
#define zt 1			//�ӽ���״̬��1λ���ܣ�0λ���� 

union un{
	unsigned int i;
	unsigned char c[4];
	unsigned short s[2];
};

void pf(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
void KeyExpansion_one(unsigned int *Key,unsigned int *W);
void KeyExpansion_two(unsigned int *Key,unsigned int *W);
void csh_jia(unsigned int *B0,unsigned int *B1,unsigned int *S_BOX0,unsigned int *S_BOX1);		//���ܳ�ʼ�� 
void csh_jie(unsigned int *B0,unsigned int *B1,unsigned int *S_BOX0,unsigned int *S_BOX1);		//���ܳ�ʼ�� 
void fz(unsigned int *W);																		//������Կ��ת 
void Performance(int s);																		//�ٶȲ��Ժ�����sΪ������ 
void Encryption(); 
void Decryption();
