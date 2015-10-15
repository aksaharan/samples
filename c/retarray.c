#include <stdio.h>

typedef char* ARRAY_POINTER_TYPE;
typedef char ARRAY_TYPE[10];

#define ARRAY_TYPE_INITIALIZER {0}

static ARRAY_POINTER_TYPE
_TestFunction(ARRAY_TYPE szValue);

int
main(void)
{
	ARRAY_TYPE szValue = ARRAY_TYPE_INITIALIZER;

	fprintf(stderr, "Array Before Call [%s]\n", szValue);
	_TestFunction(szValue);
	fprintf(stderr, "Array After Call [%s]\n", szValue);
	return 0;
}

static ARRAY_POINTER_TYPE
_TestFunction(ARRAY_TYPE szValue)
{
	strcpy(szValue, "123");
	return szValue;
}
