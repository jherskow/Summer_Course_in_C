#include "MyString.h"

int main()
{
	char *str1 = "abab";
	char *str2 = "aba";
	int res = countSubStr(str1,str2,0);
	if (1 != res)
	{
		printf("calling countSubStr with str1: \"abab\", str2: \"aba\" and isCyclic=0 should return 1\n");
		return 1;
	}

	res = countSubStr(str1,str2,1);
	if (2 != res)
	{
		printf("calling countSubStr with str1: \"abab\", str2: \"aba\" and isCyclic=1 should return 2\n");
		return 1;
	}

	printf("running example passed\n");
	
	return 0;
}
