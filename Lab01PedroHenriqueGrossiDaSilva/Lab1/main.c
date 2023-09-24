#include <stdio.h>
#include <stdlib.h>
#include "floor.h"
#include "verify_input.h"

int main(int argc, char *argv[])
{
	int is_number = 0;

	switch (argc)
	{
	case 1:
		printf("\nNo argument passed through command line!");
		printf("\nArgument allowed = 1 decimal number\n");
		break;
	case 2:
		is_number = verify_number(argv[1]);
		if (is_number == 1)
		{
			float num = atof(argv[1]);
			float_floor(num);
		} else
		{
			printf("\nArgument passed through command line not allowed!");
			printf("\nArgument allowed = 1 decimal number\n");
		}
		break;
	default:
		printf("\nToo many arguments passed through command line!");
		printf("\nArguments allowed = 1 decimal number\n");
		break;
	}
	return (0);
}
