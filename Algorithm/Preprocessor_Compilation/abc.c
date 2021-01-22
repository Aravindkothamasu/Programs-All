#include"def.h"
int check(char *a)
{
	FILE *fp = fopen(a,"r+");
	int i,j,k;
	char d[10]="include";
	bzero(s,sizeof(s));
	while(fgets(s,250,fp))
	{
		for(i=0;s[i];i++)
		{
			if(s[i]==' '||s[i]==9);
			else if(s[i]=='#')
			{	
				printf("#\n");
				for(j=i+1;d[j-i-1];j++) 
				{	
					if(s[j]!=d[j-i-1])	
						goto abc;
				}
				for(k=j;s[k];k++)
				{	
					if(s[k]==' '||s[k]==9);
					else if(s[k]=='<')
						head(s,k,0);
					else if(s[k]=='"')
						head(s,k,1);
					else 
						goto abc;
				}
			}
			else 
				break;
		}	
abc:
		bzero(s,sizeof(s));
	}
}
void head(char *s,int k,int dif)
{
	char p[35],ch[700];
	int i,j,her=open("phdr",O_RDWR|O_APPEND|O_CREAT,0664),as=13;
	bzero(p,sizeof(p));
	if(dif==0)
		strcpy(p,"/usr/include/");
	else 
		as=0;
	printf("s= %s   \n\n from : %s\n",s,(s+k));
	for(i=++k;s[i];i++)
	{
		if(s[i]==' ')
		{
			printf("fatal error: %s\n",(s+k));
			exit(0);
		}
		else if(s[i]=='>'||s[i]=='"')
			break;
		p[as+i-k]=s[i];
	}
	p[as+i-k]=0;
	printf("p = %s\n",p);
	dest = open(p,O_RDWR);
	if(dest<=0)
	{	
		printf("fatal error:%s\n",p);
		exit(0);
	}
	while(read(dest,ch,sizeof(ch)))
	{
		write(her,ch,strlen(ch));	
		bzero(ch,sizeof(ch));
	}
	close(dest);
	close(her);
}
