#include <stdio.h>

#define MAX_NUMBER_LENGTH 50

int main(void)
{
	int x, y, z;
	char szName[100] = "";
	char szOriginID[MAX_NUMBER_LENGTH] = "";
    char szMaleCount[MAX_NUMBER_LENGTH] = "";
    char szFemaleCount[MAX_NUMBER_LENGTH] = "";
    char szFirstCount[MAX_NUMBER_LENGTH] = "";
    char szLastCount[MAX_NUMBER_LENGTH] = "";
    char szPlaceCount[MAX_NUMBER_LENGTH] = "";
    char szOriginal[MAX_NUMBER_LENGTH] = "";

	const char* szLine = "1,JOCELYN, , , , , ,0";
	int nCount = sscanf(szLine, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                szOriginID, szName, szMaleCount,
                szFemaleCount, szFirstCount, szLastCount,
                szPlaceCount, szOriginal);

    fprintf(stderr, "Failed to extract record out of the entry [%s] at \n"
		"[%s, %s, %s, %s, %s, %s, %s, %s] with return [%d]\n",
        szLine, szName, szOriginID, szMaleCount, szFemaleCount, szFirstCount,
		szLastCount, szPlaceCount, szOriginal, nCount);
	return 0;
}
