#include "stdafx.h"
#include "wmmintrin.h"
#include "aes.h"
#include <stdio.h>
union int64{
	__m128i a;
	unsigned int i[4];
};

int main()
{
    
	unsigned int W[4*(Nr+1)],Key[lk/32]={0x12345678,0x12345678,0x12345678,0x12345678};//初始密钥 
	
	unsigned int i,t1,t2;
	
    __m128i a,key_z;
    int64 res;
    int64 key[Nr+1];
	
	printf("\n\n*******************************\n\n");
	
	KeyExpansion_one(Key,W);  //圈子密钥的生成
		
	a.m128i_i64[1]=0x8899aabbccddeeff;  //明文
	a.m128i_i64[0]=0x0123456789abcdef;  //明文

	key_z.m128i_i64[0]= 0; key_z.m128i_i64[1]= 0;
	

	printf("待加密: 0x%17llx%17llx\n", a.m128i_i64[0], a.m128i_i64[1]);

	for(i=0;i<Nr+1;i++){
		key[i].i[0]=W[4*i+0];   //每四个w组成一个key
		key[i].i[1]=W[4*i+1];
		key[i].i[2]=W[4*i+2];
		key[i].i[3]=W[4*i+3];
	}//*/
	int s=1000,j;

		a = _mm_xor_si128(a, key[0].a);  //字节矩阵与圈子密钥模2加
		a = _mm_aesenc_si128(a, key[1].a);  // 执行一轮 AES 加密
		a = _mm_aesenc_si128(a, key[2].a);
		a = _mm_aesenc_si128(a, key[3].a);
		a = _mm_aesenc_si128(a, key[4].a);
		a = _mm_aesenc_si128(a, key[5].a);
		a = _mm_aesenc_si128(a, key[6].a);
		a = _mm_aesenc_si128(a, key[7].a);
		a = _mm_aesenc_si128(a, key[8].a);
		a = _mm_aesenc_si128(a, key[9].a);
		a = _mm_aesenclast_si128(a, key[10].a); // 执行最后一轮的 AES 加密 

 	//pf(a.i[0],a.i[1],a.i[2],a.i[3]);  //输出abcd矩阵
	  
	
	printf("加密后：0x%17llx%17llx\n",a.m128i_i64[0], a.m128i_i64[1]);
	
	key[1].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[1].a, key_z),key_z);//生成脱密密钥
	key[2].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[2].a, key_z),key_z);
	key[3].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[3].a, key_z),key_z);
	key[4].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[4].a, key_z),key_z);
	key[5].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[5].a, key_z),key_z);
	key[6].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[6].a, key_z),key_z);
	key[7].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[7].a, key_z),key_z);
	key[8].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[8].a, key_z),key_z);
	key[9].a=_mm_aesdec_si128(_mm_aesenclast_si128(key[9].a, key_z),key_z);
	
		a=_mm_xor_si128(a,key[10].a);
		a=_mm_aesdec_si128(a, key[9].a);
		a=_mm_aesdec_si128(a, key[8].a);
		a=_mm_aesdec_si128(a, key[7].a);
		a=_mm_aesdec_si128(a, key[6].a);
		a=_mm_aesdec_si128(a, key[5].a);
		a=_mm_aesdec_si128(a, key[4].a);
		a=_mm_aesdec_si128(a, key[3].a);
		a=_mm_aesdec_si128(a, key[2].a);
		a=_mm_aesdec_si128(a, key[1].a);
		a=_mm_aesdeclast_si128(a , key[0].a);
		
		printf("****\n解密后：0x%17llx%17llx\n",a.m128i_i64[0], a.m128i_i64[1]);
		
	/*	a=_mm_xor_si128(a,key[0].a);
		a=_mm_aesenc_si128(a, key[1].a);
		a=_mm_aesenclast_si128(a, key[0].a);
		printf("解密后：0x%17llx%17llx\n",a[0], a[1]);
		a=_mm_xor_si128(a,key[0].a);
		a=_mm_aesdec_si128(a, key[2].a);
		a=_mm_aesdeclast_si128(a, key[0].a);
		printf("解密后：0x%17llx%17llx\n",a[0], a[1]);//*/

		KeyExpansion_one(Key, W);
		for (i = 0; i<Nr + 1; i++) {
			key[i].i[0] = W[4 * i + 0];   //每四个w组成一个key
			key[i].i[1] = W[4 * i + 1];
			key[i].i[2] = W[4 * i + 2];
			key[i].i[3] = W[4 * i + 3];
		}//*/
		clock_t start, end;
		start = clock();
		for (j = 0; j < 8192 * s; j++) {
			a = _mm_xor_si128(a, key[0].a);  //字节矩阵与圈子密钥模2加
			a = _mm_aesenc_si128(a, key[1].a);  // 执行一轮 AES 加密
			a = _mm_aesenc_si128(a, key[2].a);
			a = _mm_aesenc_si128(a, key[3].a);
			a = _mm_aesenc_si128(a, key[4].a);
			a = _mm_aesenc_si128(a, key[5].a);
			a = _mm_aesenc_si128(a, key[6].a);
			a = _mm_aesenc_si128(a, key[7].a);
			a = _mm_aesenc_si128(a, key[8].a);
			a = _mm_aesenc_si128(a, key[9].a);
			a = _mm_aesenclast_si128(a, key[10].a); // 执行最后一轮的 AES 加密 
			key[1].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[1].a, key_z), key_z);//生成脱密密钥
			key[2].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[2].a, key_z), key_z);
			key[3].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[3].a, key_z), key_z);
			key[4].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[4].a, key_z), key_z);
			key[5].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[5].a, key_z), key_z);
			key[6].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[6].a, key_z), key_z);
			key[7].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[7].a, key_z), key_z);
			key[8].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[8].a, key_z), key_z);
			key[9].a = _mm_aesdec_si128(_mm_aesenclast_si128(key[9].a, key_z), key_z);

			a = _mm_xor_si128(a, key[10].a);
			a = _mm_aesdec_si128(a, key[9].a);
			a = _mm_aesdec_si128(a, key[8].a);
			a = _mm_aesdec_si128(a, key[7].a);
			a = _mm_aesdec_si128(a, key[6].a);
			a = _mm_aesdec_si128(a, key[5].a);
			a = _mm_aesdec_si128(a, key[4].a);
			a = _mm_aesdec_si128(a, key[3].a);
			a = _mm_aesdec_si128(a, key[2].a);
			a = _mm_aesdec_si128(a, key[1].a);
			a = _mm_aesdeclast_si128(a, key[0].a);
		}										//pf(a.i[0],a.i[1],a.i[2],a.i[3]);  //输出abcd矩阵
		end = clock();
		printf("SSE处理指令下AES计算8192000次加密所需时间:%.4fs\n", (float)(end - start) / CLK_TCK);
	getchar();
	getchar();
	
    return 0;
}