#ifndef __BLOWFISH_H
#define __BLOWFISH_H
#define MAXKEYBYTES 56			/* 448 bits */
typedef struct BLOWFISH_CTX{
	unsigned long P[18];	//16+2
	unsigned long S[4][256];
} BLOWFISH_CTX;
#define N 16
//unsigned long F(BLOWFISH_CTX * ctx, unsigned long x);
void Blowfish_Init(BLOWFISH_CTX * ctx, unsigned char *key, int keyLen);
void Blowfish_Encrypt(BLOWFISH_CTX * ctx, unsigned long *xl, unsigned long *xr);
void Blowfish_Decrypt(BLOWFISH_CTX * ctx, unsigned long *xl, unsigned long *xr);
#endif
