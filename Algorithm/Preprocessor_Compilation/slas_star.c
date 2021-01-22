#include"header.h" 
void slash_star(char *input,char *output) 
{ 
   FILE *fi = fopen(input,"r+"); 	//Input file
   FILE *fo = fopen(output,"w");	//output file after this function
   char p[250];

   int i=0,j=0,dou_qout=0,Var;
   bzero(s,sizeof(s));		
   flg=0;				

   if( (fi==0) || (fo==0))
   {
	printf("errno = %d, Reason = %s\n",errno,strerror(errno));
	return;	
   }

   while(fgets(s,250,fi)) 
   {
	for(i=0;s[i];i++) 
	{ 
	  if(!flg)			
	   if(s[i]=='"' && ( (s[i-1]!='\\') || (s[i-1]!=39&&s[i+1]!=39) ) )       //starting of the string
	   {
		dou_qout=!dou_qout;				//trigger the flag
	   }

	  if(flg)		//for */
	  {
	         if(s[i]=='*' && s[i+1]=='/')
		 {	
	  	       end=i;			
		       flg=0;
		       for(j=0;s[i];i++,j++)
			      p[j]=s[i+2];
		        p[j]=0;
			j=0;
			bzero(s,sizeof(s));
			strcpy(s,p);
			flg = 0;
		 }
	 }
 	 else if(!flg)				//for /* 
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
					s[Var-2] = s[Var];
				    
				     s[Var-2] = 0;	
				     i-=2;
					goto abcde;	
				}
				else 
  				{
//				   for( Var = i ; s[Var] ;  Var++ )		//eliminating /*
				 	s[Var-2] = s[Var];
//				    s[Var-2] = 0;			//For \0
				    i--;
				}

			if(s[i]==0)			//for outer for loop
				i--;
		/*	    s[star]=0;					
			    flg=0;
			if(s[j] == '*' && s[j+1] == '/') 
				{
				   end = j+2;
				   break;
				}

			if(s[j]=='*') 
			{
			    for( ;s[end];end++,star++) 
			 	s[star]=s[end];
			    s[star]=0;					
			    flg=0;
			}*/
			if(!flg)
			{
abcde:
				s[i]=0;
				fputs(s,fo);
			}

		  }		
       }
/*	if(flg)
		if(s[i]==0) 
		{  bzero(s,sizeof(s));
			continue;
		}	*/
	if(!flg && s[0]!='/' && s[1]!='*')
	{
	    fputs(s,fo);
	    bzero(s,sizeof(s));
	}
   }
		fclose(fo);
		fclose(fi);
}

/*void main()
{
	
	slash_star("double_slas.c","3456.c");
	double_slash("3456.c","7890.c");
//	system("rm 3456");
}*/
void main()
{
	
	slash_star("ARAVIND","3456.c");
//	double_slash("3456.c","7890.c");
//	system("rm 3456");
}
