#ifndef AES_H
#define AES_H

#include<stdio.h>

/* Key should be strictly of length 16 */
int aes_encrypt(char *data, char *key);
int aes_decrypt(char *data, char *key);

int aes_encrypt_file(FILE *input, FILE *output, char *key);
int aes_decrypt_file(FILE *input, FILE *output, char *key);

#endif
