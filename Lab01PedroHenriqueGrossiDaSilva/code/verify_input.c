#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "verify_input.h"

int verify_number(char *input)
{
	int is_number = 1;
	int decimal = 1;
	int lenght = strlen(input);

	for (int i=0;i<lenght; i++)
	{
		if (!isdigit(input[i]))
		{
			if (decimal == 1 && input[i] == '.')
			{
				decimal = 0;
			}
			else
			{
				is_number = 0;
				break;
			}
		}
	}
	return (is_number);
}
