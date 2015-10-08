#include <wchar.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	wchar_t* szValue = L"This is Hello World for the UNICODE character set";
	wchar_t* szName = L"UNICODE set";
	wchar_t* szHelloWorld = L"Hello World";

	errno = 0;
	fwide(stderr, sizeof(wchar_t));
	fwprintf(stderr, L"Error number after fwide [%s, %d]\n", strerror(errno), errno);
	fwprintf(stderr, L"This is the unicode print... sizeof(wchar_t*) = %d, sizof(wchar_t) = %d\n",
		sizeof(szValue), sizeof(szValue[0]));
	fwprintf(stderr, L"[%s == %s] = %d\n", szName, szHelloWorld, wcscmp(szName, szHelloWorld));
	fwprintf(stderr, L"[%s == %s] = %d\n", szName, szName, wcscmp(szName, szName));
	fwprintf(stderr, L"[%s == %s] = %d\n", szHelloWorld, szName, wcscmp(szHelloWorld, szName));
	return 0;
}
