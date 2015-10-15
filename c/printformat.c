#include <stdio.h>

int main(void)
{
	fprintf(stderr, "%03d, %03s, %-03d, %-03s\n", 12, "12", 12345, "12345");
	fprintf(stderr, "%*d%*d, %*s%*s\n"
				"%*s%*s\n",
			5, 12345, 2, 12,
			5, "12345", 2, "12",
			5, "345", 2, "2");
	return 0;
}
