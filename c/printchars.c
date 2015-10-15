#include <ctype.h>
#include <stdio.h>

int main(void)
{
	int i;
	for (i = 0; i < 256; ++i) {
		fprintf(stdout, "\n\t{%d, \'%c\', \'%c\'},", i,
			 isspace(i) || iscntrl(i) || isblank(i) ? ' ' : (char)i,
			 isspace(i) ? ' ' : toupper((char)i));
	}
	fprintf(stdout, "\n");
}
