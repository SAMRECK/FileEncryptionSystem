

#include<stdio.h>
#include<string.h>
#include "AES/aes.c"
void AES_main()
{
	
	FILE *fp_i,*fp_o;
	char input_file_name[20],output_file_name[20];
	
	int type;
	printf("\nEnter Operation No:\n");
	printf("\n\tEnter [1] to Encrypt File\n");
	printf("\n\tEnter [2] to Decrypt File\n");
	scanf("%d",&type);
	
	printf("\nEnter Input File path:\t");
	scanf("%s",input_file_name);
	printf("\nEnter Output File path:\t");
	scanf("%s",output_file_name);
	
	fp_i=fopen(input_file_name,"rb");
	fp_o=fopen(output_file_name,"wb");
	
	char key[16];
	printf("\nEnter key:\t");
	scanf("%s",key);


	if(type == 1)
                {
		aes_encrypt_file(fp_i, fp_o, key);
		printf("\tFile Encrypted Successfully.....\n");
		} 
	else if(type == 2)
		{
		aes_decrypt_file(fp_i, fp_o, key);
		printf("\tFile Decrypted Successfully.....\n");
		}
	else
		printf("!!! Please enter correct input !!!");

	fclose(fp_i);
	fclose(fp_o);
}
