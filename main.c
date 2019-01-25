
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "blowfish.h"
#include "secure.c"


void start()
{
 	printf("  ___ 	       ___       ___	      ___  _____  ___           \n");
	printf(" |     ||   | (   )     (   ) |    | (   )   |   |    ||      ||\n");        
	printf(" |___  | |  | |	    __  |___   |  |  |___    |   |___ | |    | |\n");
	printf(" |     |  | | |	            |   ||       |   |   |    |  |  |  |\n");
	printf(" |___  |   || (___)     (___)   ||   (___)   |   |___ |   ||   |\n");
}

int Blowfish_main() {
	
	int type;
	printf("Enter [1] for Encryption..\n");
	printf("Enter [2] for Decryption..\n");
	scanf("%d",&type);

	int keylen, flag = 0;
	char k, tmp;
	char filename[50], dirname[50], filenametmp[50], sdir[50];
	int fileindex = 0, filecount, dirindex = 0, dircount, delfile;
	unsigned int retstrlen, retstrlen1;
	unsigned char key[56];
	unsigned long l, r, filelen;
	unsigned char *cr, *cl;
	short i = -1;
	unsigned long percent;
	unsigned long count;
	if(type < 1 || type > 2) {
		errno = EINVAL;
		perror("Select [1] or [2] :");
		return errno;
	}
        printf("\nEnter key:\t");
	scanf("%s",key);
	keylen = strlen(key);
	/************************Strong key*********************/
	
		while(++i < keylen) {
			if(key[i] < 97 || key[i] > 122) {
				flag = 1;
				break;
			}
		
		
	
	keylen = strlen(key);
	if(keylen < 4 || keylen > 56) {	/*Argv[1] is my key length 32-448 bits */
		perror("Key should be greater than 4 bytes and less than 56 bytes : ");
		return -1;
	}
	/**********************Strong key***************************************/
		FILE *fp1;
		FILE *fp2;
		char input_file_name[20],output_file_name[20];
		printf("\n\tEnter Input File path:\t");
		scanf("%s",input_file_name);
		printf("\n\tEnter Output File path:\t");
		scanf("%s",output_file_name);
		fp1 = fopen(input_file_name, "r");
			if(fp1 == NULL) {
				perror("\tOpened failed : ");
				return errno;
			}
			BLOWFISH_CTX ctx;
			Blowfish_Init(&ctx, key, keylen);
			percent = 0;
			if(type==1) {
				
				strcat(output_file_name, ".enc");
				fp2=fopen(output_file_name,"wb");
				if(fp2 == NULL) {
					perror("\tOpened failed : ");
					return errno;
				}
				fseek(fp1 , 0L, SEEK_END);
				filelen = ftell(fp1);
				rewind(fp1);
				filelen = filelen + keylen;	//Don't want to store bytes directly
				fprintf(fp2, "%lu", filelen);
				while(!feof(fp1)) {
					l = r = 0X00000000;
					retstrlen1 = fread(&l, sizeof(unsigned long), 1, fp1);
					retstrlen = fread(&r, sizeof(unsigned long), 1, fp1);
					i = 0;
					Blowfish_Encrypt(&ctx, &l, &r);
					cl = &l;
					cr = &r;

					for(i = 0; i < 8; i++) {
						fprintf(fp2, "%c", cl[i]);
					}
					for(i = 0; i < 8; i++) {
						fprintf(fp2, "%c", cr[i]);
					}
					printf("\t\rIn progress %d%%", (int)((16 * percent++ * 100) / (filelen - 8)));
					fflush(stdout);
				}
			} 
			else if(type==2) {
				
				strcat(output_file_name, ".dec");
				fp2 = fopen(output_file_name, "w");
				if(fp2 == NULL) {
					perror("\tOpened failed : ");
					return errno;
				}
				fscanf(fp1, "%lu", &filelen);
				filelen = filelen - keylen;
				while(!feof(fp1)) {
					l = r = 0X00000000;
					retstrlen1 = fread(&l, sizeof(unsigned long), 1, fp1);
					retstrlen = fread(&r, sizeof(unsigned long), 1, fp1);
					i = 0;
					
					Blowfish_Decrypt(&ctx, &l, &r);
					cl = &l;
					cr = &r;
					for(i = 0; i < 8; i++) {
						if(count > filelen - 1)
							break;
						fprintf(fp2, "%c", cl[i]);
						count++;
					}
					for(i = 0; i < 8; i++) {
						if(count > filelen - 1)
							break;
						fprintf(fp2, "%c", cr[i]);
						count++;
					}
					printf("\t\rIn progress %d%%", (int)((16 * percent++ * 100) / (filelen - 8)));
					fflush(stdout);
				}
			}
			
			
			fclose(fp1);
			fclose(fp2);
			printf("\n");
			if(type==1)
				printf("\tYour data is successfully encrypted in %s\n", output_file_name);
			else{
				printf("\tYour data is successfully decrypted in %s\n",output_file_name);
			break;}
		}
		return 0;
}

int main()
{
	
	int op;
	start();
	printf("\n\n");
	printf("\tEnter [1] to select AES \n");
	printf("\tEnter [2] to select Blowfish\n");
	scanf("%d",&op);
	if(op == 1)
		AES_main();
	else Blowfish_main();
	return 0;
}

