#include"header.h"
void slash_star(char *p,char *q)
{
	FILE *fi = fopen(p,"r");
	FILE *fo = fopen(q,"w+");

	int i,j,k;
	int qout=0,flg=0,str=0;

	if( (fi||fo) == 0)
	{
		printf("can't able open file\n");
		return;
	}	

	while(fgets(s,fi,sizeof(s))) 
	{ 
		for(i=0;s[i];i++) 
		{ 
		   if(!str) 
			if(s[i]=='"' && ( s[i-1]!='\\' || (s[i-1]!=39 && s[i+1]!=39))) 
				qout = !qout; 

			if(!qout) 
			   if( s[i]== '/' && s[i+1]== '*' ) 
			   { 
				srt = i; 
				for(j=i+2;s[j];j++) 
					if( s[j]=='*' && s[j+1] == '/' ) 
					{ 
						srt = 0; 
						goto abcde; 
					} 
					else 
						s[j-2] = s[j]; 
			  } 
			
			if(  )
			{
				
		
			}

			if(!srt)		
			{
				abcde:
				fputs(s,fo);	
			}		
	        }
	}
