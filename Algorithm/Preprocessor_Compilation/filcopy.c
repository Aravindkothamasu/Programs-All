#include"header.h"
void copy_fil(char *a) 
{ 
	int fd = open(a,O_RDONLY);
	int fp = open("1111",O_CREAT|O_RDWR|O_APPEND,0664); 
	if(fp<=0||fd<=0) 
	{ 
		perror("open"); 
		return;	
	} 
	perror("open"); 

	while(read(fd,s,sizeof(s))) 
	{ 
		write(fp,s,strlen(s)); 
		bzero(s,sizeof(s)); 
//		sleep(1); 
	} 

	lseek(sou,0,SEEK_SET); 
	lseek(dest,0,SEEK_SET); 
	close(dest);
}	
