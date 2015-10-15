#include <time.h>
#include <stdio.h>
#include <string.h>

#define LOOP_COUNT			50000000
#define MAX_BUFFER_LENGTH	1024

static time_t
_PrintfStats(void);

static time_t
_StrcatStats(void);

int main(void)
{
	fprintf(stderr, "The Execution Times are [%u, %u]\n",
		_PrintfStats(), _StrcatStats());
	return 0;
}

static time_t
_PrintfStats(void)
{
	size_t nIndex = 0;
	char szBuffer[MAX_BUFFER_LENGTH];
	time_t nStartTime = 0, nEndTime = 0;

	nStartTime = time(NULL);	
	for (nIndex = 0; nIndex < LOOP_COUNT; ++nIndex) {
		snprintf(szBuffer, sizeof(szBuffer)/sizeof(szBuffer[0]),
			"%s : %s", "First", "Second");
	}
	nEndTime = time(NULL);
	return (time_t)difftime(nEndTime, nStartTime);
}

static time_t
_StrcatStats(void)
{
	size_t nIndex = 0;
	char szBuffer[MAX_BUFFER_LENGTH];
	time_t nStartTime = 0, nEndTime = 0;

	nStartTime = time(NULL);	
	for (nIndex = 0; nIndex < LOOP_COUNT; ++nIndex) {
		szBuffer[0] = 0;
		strcat(szBuffer, "First");
		strcat(szBuffer, " : ");
		strcat(szBuffer, "Second");
	}
	nEndTime = time(NULL);
	return (time_t)difftime(nEndTime, nStartTime);
}
