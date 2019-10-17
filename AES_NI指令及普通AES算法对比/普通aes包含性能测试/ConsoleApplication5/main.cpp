#include"stdafx.h"
#include <stdint.h>
#include <iostream>
#include"stdio.h"
#include "aes.h"
#include"time.h"
int main(int argc, char *argv[]) {
	uint8_t i, r;

	/* 128 bit key */
	uint8_t key[AES_BLOCK_SIZE] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};  //密钥
	uint8_t plaintext[AES_BLOCK_SIZE]= { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff }; //明文
	uint8_t ciphertext[AES_BLOCK_SIZE]; //密文


	const uint8_t const_cipher[AES_BLOCK_SIZE] = {
		//0xff, 0x0b, 0x84, 0x4a, 0x08, 0x53, 0xbf, 0x7c,
		//0x69, 0x34, 0xab, 0x43, 0x64, 0x14, 0x8f, 0xb9,
		0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
		0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a,
	};
	
	uint8_t roundkeys[AES_ROUND_KEY_SIZE];  //圈子密钥

	int text[AES_BLOCK_SIZE];

	printf("\n--------------------------------------------------------\n");
	printf("Plain text:\n");
	/*for (int t = 0; t < AES_BLOCK_SIZE; t++) {
		scanf_s("%x", &text[t]);
		plaintext[t] = (uint8_t)text[t];
	}
	getchar();
	*/
	for (int t = 0; t < AES_BLOCK_SIZE; t++) {
		printf("%2x ", plaintext[t]);
	}
	
	printf("\nkey:\n");
	/*for (i = 0; i < AES_BLOCK_SIZE; i++) {
		scanf_s("%x", &text[i]);
		key[i] = (uint8_t)text[i];
	}
	getchar();*/
	for (int t = 0; t < AES_BLOCK_SIZE; t++) {
		printf("%2x ", key[t]);
	}
	printf("\n--------------------------------------------------------\n");

	// key schedule
	aes_key_schedule_128(key, roundkeys);
	printf("Round Keys:\n");
	for ( r = 0; r <= AES_ROUNDS; r++ ) {
		for (i = 0; i < AES_BLOCK_SIZE; i++) {
			printf("%2x ", roundkeys[r*AES_BLOCK_SIZE+i]);
		}
		printf("\n");
	}
	printf("\n");
	clock_t start, end;
	start = clock();
	for (int k = 0; k <81920; k++) {
	// encryption
	aes_encrypt_128(roundkeys, plaintext, ciphertext);
	


	// decryption
	aes_decrypt_128(roundkeys, ciphertext, ciphertext);
	
	}
	end = clock();
	printf("Plain text:\n");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%2x ", ciphertext[i]);
	}
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		if (ciphertext[i] != plaintext[i]) { break; }
	}
	if (AES_BLOCK_SIZE != i) { printf("\nDECRYPT WRONG\n\n"); }
	else { printf("\nDECRYPT CORRECT\n\n"); }
	printf("Cipher text:\n");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%2x ", ciphertext[i]);
	}
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		if (ciphertext[i] != const_cipher[i]) { break; }
	}
	if (AES_BLOCK_SIZE != i) { printf("\nENCRYPT WRONG\n\n"); }
	else { printf("\nENCRYPT CORRECT\n\n"); }
	printf("普通AES计算81920加脱密所需时间:%.4fs\n", (float)(end - start) / CLK_TCK);
	getchar();
	return 0;
}
