
#include"aes.c"

void test_encrypt()
{
	FILE *fp_input, *fp_output;
	fp_input = fopen("README", "rb");
	fp_output = fopen("readme.enc", "wb");

	char *key = "mynameisslimshad";

	aes_encrypt_file(fp_input, fp_output, key);

	fclose(fp_input);
	fclose(fp_output);
}

void test_decrypt()
{
	FILE *fp_input, *fp_output;
	fp_input = fopen("readme.enc", "rb");
	fp_output = fopen("readme.dec", "wb");

	char *key = "mynameisslimshad";

	aes_decrypt_file(fp_input, fp_output, key);

	fclose(fp_input);
	fclose(fp_output);
}

void main(int argc, char* argv[])
{	
	test_encrypt();
	test_decrypt();
}
