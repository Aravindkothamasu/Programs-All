#include"header.h"
void remove_space(char *a)	
{
	int i,j;
	char ch = ' ';
	for(i=0;a[i];i++)
		if(a[i]==ch)
		{	
			for(j=i;a[j];j++)
				a[j] = a[j+1];
			i--;
		}
}
