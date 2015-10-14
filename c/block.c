#include <stdio.h>

#define GET_VAL(type) \
	{ \
		type x; \
		x = 10; \
		return 10; \
	}

int main(void)
{
	int x = 0;
	x = GET_VAL(int);
	return 0;
}
