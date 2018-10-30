#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
	const char *sequence = "12345678";		// Stable length 8 
	char sale[12];
	strcpy(sale, "$1$");	// MD5 prefix
	strcat(sale, sequence);

	const char *input = "Hello Crypt!";
	char *output;
	int times = 0;
	time_t time_init = time(NULL);

	while (1)
	{
		output = crypt(input, sale);

		if (output == NULL || output[0] == '*')
		{
			perror("Crypt error:");
			return -1;
		}

		printf("Input: %s\n", input);
		printf("Output: %s\n", output);
		printf("Times: %i, Seconds: %i\n", times, (int)(time(NULL) - time_init));

		times++;
	}

	return 0;
}
