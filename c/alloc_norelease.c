#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i = 0;
	for (i = 0; i < INT_MAX; ++i) {
		malloc(100);
		sleep(0);
	}
}
