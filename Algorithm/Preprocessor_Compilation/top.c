#include"header.h"
int check(char *a)
{
	FILE *fp = fopen(a,"r+");
	int i,j,k;
	char d[10]="include";					//searching for word include
	bzero(s,sizeof(s));
	while(fgets(s,250,fp))
	{
		for(i=0;s[i];i++)				//iterating loop upto last
		{
			if(s[i]==' '||s[i]==9);			//ignoring spaces
			else if(s[i]=='#')			//If # was found
			{	
				for(j=i+1;d[j-i-1];j++) 	//checking define keyword
				{	
					if(s[j]==' '||s[j]==9)
						i++;
					else if(s[j]!=d[j-i-1])	//If not goto abc(jump)	
						goto abc;	//If define keyword is not found goto abc
				}
				for(k=j;s[k];k++)		//searching for header file name
				{	
					if(s[k]==' '||s[k]==9);
					else if(s[k]=='<')	//if it is pre define phead with after the '<'
						phead(s,k+1);
					else if(s[k]=='"')	//if it is user define uhead with after the '"'
						uhead(s,k);
					else 			//other than that ignore this line
						goto abc;
				}
			}
			else 
				break;
		}	
abc:
		bzero(s,sizeof(s));				//making as clean
	}
}

void phead(char *s,int k)
{
	char p[35],ch[700];
// "p" is an array that represents the header file search path
	int i,j,her=open("hddr",O_RDWR|O_APPEND|O_CREAT,0664),as=13,destt;
	bzero(p,sizeof(p));
/*in user define header if it is "sys/types.h" if any header in the form of "sys" then it has to search in
"/usr/include/linux" in that folder  s[k]=s,s[k+1]=y,s[k+2]=s,s[k+3]='//'*/

	if(s[k]=='s' && s[k+1]=='y' && s[k+2]=='s' && s[k+3]=='/')
	{
		strcpy(p,"/usr/include/linux/");	
		strncpy(s,(s+k+4),20);			//truncating "#include<sys/<______.h>" into "______.h>"
		k=0;					//k is staring position
		as = 19;	}			//as is length of "/usr/include/linux"
	else						/*if it is normal search in  /usr/include*/
		strcpy(p,"/usr/include/");

	for(i=k;s[i];i++)		
	{
		if(s[i]==' '||s[i]==9)			//after "<" any space then it is a fatal error
		{
			printf("fatal error: %s\n",(s+k));
			exit(0);
		}
		else if(s[i]=='>')			//if ">" occur come out of loop
			break;
		p[as+i-k]=s[i];				//upto then copy to p array
	}
	p[as+i-k]=0;					//end of that array
	printf("%s\n",p);				//printing that array means path of that array
	if((destt = open(p,O_RDONLY))<=0)		//opening that with system cal
	{	
		printf("fatal error:%s\n",p);		//if it can't open error fatal error file not found	
		exit(0);				//terminate the program
	}
	while(read(destt,ch,sizeof(ch)))		//read from that pre-define file store into array "ch"
	{
		write(her,ch,strlen(ch));		//write into the "hddr" file 
		bzero(ch,sizeof(ch));
	}
	close(destt);					//close the both the files
	close(her);
}


/*for user-define header file if that particular not found present working directory ,then it has to search into 
predefine location*/

void uhead(char *a,int k) 	//a = the headerfile decleration ,k = starting of actual file name include<_
{	
	char p[35],ch[700];
/* p represents the path of the header file ,ch = buffer */
	int i,j,destt;
	int her=open("hddr",O_RDWR|O_APPEND|O_CREAT,0664);	//o/p of this program
	bzero(p,sizeof(p));					//clearing 
	for(i=++k;s[i];i++)
	{
		if(s[i]==' ')					//if any space occur '"" then fatal error
		{
			printf("fatal error: %s\n",(s+k));
			exit(0);				//terminate program
		}
		else if(s[i]=='"')				//represents the end of file name
			break;
		p[i-k]=s[i];					//upto occurance of '"' copy to p array 
	}
	p[i-k]=0;						//end of that array
	printf("%s\n",p);					//print path and file name to be search
	FILE *a1 = fopen(p,"r+");				//open with fopen  
	if(a1)							//if it is opened succesfully
		check(p);					//treat it as new file and check() again
	else			//if it not present in pwd then it has to search in pre-define path
	{
		phead(p,0);					//phead = predeine path
		return;						//after that it should able to continue to next 
	}
	while(fgets(ch,700,a1))					// line by line
	{
		for(i=0;ch[i];i++)			
		{
			if(ch[i]=='#')				//if # in occured
				if(  (ch+i) < strstr(ch,"include") )	//checks wheather include is present or not 
					break;	//if found come out of loop no need to copy into "hddr"
				else 
					goto abc;		// if not found copy into hddr by goto statement
			else if(s[i]==' ');			//spaces are ignored 
			else					//if otherthan space and #include copy into file
			{
				abc:
				write(her,ch,strlen(ch));	//writing into file
				break;				//break come out of loop
			}
		}	
		bzero(ch,sizeof(ch));				
	}
	fclose(a1);						//close the files.
	close(destt);	
}
