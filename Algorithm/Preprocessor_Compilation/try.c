#include<stdio.h>
#include<unistd.h>
#include<error.h>
#include<strings.h>
#include<string.h>
#include"header.h"

void main()
{
	FILE *fi = fopen("double_star.c","r+");
	FILE *fo = fopen("o/p_try.c","w+");
	
	if( (fi || fo) == NULL)
	{
		printf("Error : %d Reason : %s\n",errno,strerror(errno));
		return;
	}
	
	while(fgets(s,sizeof(s),fi))
	{
		if(s[i]=='/' && s[i+1]=='*') 
		    if(!dou_qout)
		    { 
			star = i;
			flg = 1;
			for(i=i+2 ; s[i] ; i++) 
				if(s[i] == '*' && s[i+1] == '/')
				{
					flg = 0;
				    for( Var = i ; s[Var] ; Var++)
					
					i-=2;
					goto abcde;	
				}
				else 
  				{
				   for( Var = i ; s[Var] ;  Var++ )		//eliminating /*
				 	s[Var-2] = s[Var];
				    s[Var-2] = 0;			//For \0
				    i -= 2;
				}
		    }
      }
}
