#include <stdio.h>

#define _CALC_ARRAY_SIZE(x) 	(sizeof(x) / sizeof(x[0]))
#define _CHARACTER_GROUP		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"

int main(void)
{
	fprintf(stderr, "Sizeof the Alphabetset is [%d, %d]\n", _CALC_ARRAY_SIZE(_CHARACTER_GROUP), sizeof(_CHARACTER_GROUP));
	return 0;
}
