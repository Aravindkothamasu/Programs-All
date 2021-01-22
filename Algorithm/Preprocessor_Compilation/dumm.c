#include<stdio.h>
#include<string.h>
void main()
{
	char s[29]= "aravindkothamasu",d[30];
	strncpy(d,(s+2),15);
	printf("%s\n",d);

}
