#include <stdio.h>
#include <gcrypt.h>
#include <time.h>

int main()
{
	gcry_error_t err;
	gcry_md_hd_t hd;

	if ((err = gcry_md_open(&hd, GCRY_MD_MD5, 0)) != 0)
	{
		printf("Open error: %s\n", gcry_strerror(err));
		return -1;
	}

	const char *input = "Hello gcrypt!";
	unsigned char *output;
	int times = 0;
	time_t time_init = time(NULL);

	while (1)
	{
		gcry_md_write(hd, input, strlen(input));
		gcry_md_final(hd);

		if ((output = gcry_md_read(hd, 0)) == NULL)
		{
			printf("Read error\n");
			return -2;
		}

		printf("Input: %s\n", input);
		printf("Output: %s\n", output);
		printf("Times: %i, Seconds: %i\n", times, (int)(time(NULL) - time_init));

		gcry_md_reset(hd);
		times++;
	}

	gcry_md_close(hd);

	return 0;
}
