#include"header.h"
void double_slash(char *input,char *output)
{
	FILE *fi = fopen(input,"r+"); 		//opening the input file
	FILE *fo = fopen(output,"w");		//creating the o/p file 
	int i,dou_quot=0,last=0,j;
//last represents if a comment like   // and last of that line ends with -> \ <- so,next line is also to be a comment

	while(fgets(s,250,fi)) 			//reads the line-by-line
	{

if(last)		//last is non-zero means previous line comment and ends with \  <-
{
	for(i=0;s[i];i++);		//checking for w=this line also
	(s[i-2]==92) ? (last = 1) : (last = 0);		// ( s[i-2] = \ ) ,(s[i-1] = \n ) ,(s[i]=0)
	bzero(s,sizeof(s));
	continue;					//no need to continue to further
}

   for(i=0;s[i];i++) 		//iterates upto last
   { 
	if(s[i]=='"')				//when '"' occurs '//' should ignore
	      if(  (s[i-1]!='\\') && (s[i-1]!=39 && s[i+1]!=39)  )	
		//when '"' occurs it may be \" (or) '"' in these 2 cases it should not act as string format.
  dou_quot  = !dou_quot;		//if that particular is fail in above 2 cases,then only this will execute.


	if(s[i]=='/' && s[i+1]=='/') 	//if any '//' occur
	{ 

	  if(!dou_quot)				//checks wether if(dou_quot)==0 = clear otherwise ignore it
	  {
		for(j=0;s[j];j++);		//this line is in comment,then check last (\) or not
		(s[j-2]=='\\') ? (last=1):(last=0);	

		if(i==0) 			//if it occur at first starting ignore this line.
		{ 
			s[i] = 0; 		//making first character as zero 
			break; 			//come out of for loop
		} 
		if(s[i-1]!=39&&s[i+2]!=39)	//it should not be like '//' so...
		{
			s[i] = '\n'; 		//if not put the '\n' to ignore the commented part
			s[i+1] = 0; 		//end of line
			break; 
		}
	   }	
	}  
    }
   
		fputs(s,fo);
		bzero(s,sizeof(s));
    } 	

	fclose(fo);
	fclose(fi);
	bzero(s,sizeof(s));
} 

/*void main()
{
	double_slash("double_slas.c","3456");
}*/
