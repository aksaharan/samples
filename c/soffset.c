#include <stdio.h>

typedef struct {
	char 	chOffset;
	int 	nOffset;
} test_offset;

test_offset vOffset[] = {
	{'a', 1},
	{'b', 3},
	{'c', 2}
};

int main(void)
{
	fprintf(stdout, "Size of struct [%d], Array [%d], Array Element [%d]\n",
		sizeof(test_offset), sizeof(vOffset), sizeof(vOffset[0]));
	return 0;
}
