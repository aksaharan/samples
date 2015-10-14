#include <stdio.h>

typedef int INT_ARRAY[10];

INT_ARRAY vArray;

#define NX_ALIGNMENT_OFFSETS(x) \
	( \
		(sizeof(x) % sizeof(struct {int nDumbo;})) \
			? sizeof(struct {int nDumbo;}) - (sizeof(x) % sizeof(struct {int nDumbo;})) \
			: 0 \
	)

int main(void)
{
    fprintf(stdout, "Value of the sizeof is [%d]\n", sizeof(struct {int nDummyAlignmentCalculator;}));
    fprintf(stdout, "Value of the sizeof is [%d]\n", sizeof(struct {char chDummyAlignment;}));
    fprintf(stdout, "Alignment Offset for Char is [%d]\n", NX_ALIGNMENT_OFFSETS(char));
    fprintf(stdout, "Alignment Offset for Integer is [%d]\n", NX_ALIGNMENT_OFFSETS(int));
    fprintf(stdout, "Alignment Offset for Double is [%d]\n", NX_ALIGNMENT_OFFSETS(double));
    fprintf(stdout, "Sizeof [Array(10) integers] => [%d]\n", sizeof(vArray));
    fprintf(stdout, "Sizeof [Array(10) integers] => [%d]\n", sizeof(vArray)/sizeof(vArray[0]));
    fprintf(stdout, "Sizeof [Array(10) integers] => [%d]\n", sizeof(INT_ARRAY[0]));
    fprintf(stdout, "Sizeof [Array(10) integers] => [%d]\n", sizeof(INT_ARRAY)/sizeof(INT_ARRAY[0]));
    return 0;
}
