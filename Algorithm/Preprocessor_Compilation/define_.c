#include"header.h"
void define(void)
{
	FILE *fp = fopen("3333","r+");
	FILE *fd = fopen("4444","w");
	int cou=0;
	char te[10]="define";

	bzero(s,sizeof(s));
	while(fgets(fp,s,sizeof(s))!=NULL) 
	{
		for(i=0;s[i];i++) 
			if(s[i]=='#') 
			{ 
				for(j=i;s[j];j++) 
				{ 
					if(s[j]=='d') 
					{ 
						for(k=1;te[k+1];k++) 
							if(te[k]!=s[j+k]) break; 
							else; 
				


}
