#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

int main(void)
{
	void* sl = dlopen("libnamixframework.so", RTLD_NOW);
	if (sl)	{
		dlclose(sl);
	} else {
		fprintf(stderr, "Error Occured in Opening the SL [%s]", dlerror());
	}

	return 0;
}
