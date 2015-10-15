#include <math.h>
#include <stdio.h>

int main(void)
{
	size_t xSize = 4, ySize = 3;
	fprintf(stderr, "For Values [ xSize => %d, ySize => %d]\n", xSize, ySize);
    fprintf(stderr, "fabs(3 + 4)                => [%f]\n", fabs(3 + 4));
    fprintf(stderr, "fabs(3 - 4)                => [%f]\n", fabs(3 - 4));
    fprintf(stderr, "fabs((float)3 - 4)         => [%f]\n", fabs((float)3 - 4));
	fprintf(stderr, "fabs(ySize - xSize)        => [%f]\n", fabs(ySize - xSize));
	fprintf(stderr, "fabs((float)ySize - xSize) => [%f]\n", fabs((float)ySize - xSize));
    fprintf(stderr, "fabs(-1)                   => [%f]\n", fabs(-1));
    fprintf(stderr, "fabs(4 - 3)                => [%f]\n", fabs(4 - 3));
    fprintf(stderr, "fabs((float)4 - 3)         => [%f]\n", fabs((float)4 - 3));
	fprintf(stderr, "fabs(xSize - ySize)        => [%f]\n", fabs(xSize - ySize));
	fprintf(stderr, "fabs((float)xSize - ySize) => [%f]\n", fabs((float)xSize - ySize));
    fprintf(stderr, "fabs(1)                    => [%f]\n", fabs(1));
	return 0;
}
