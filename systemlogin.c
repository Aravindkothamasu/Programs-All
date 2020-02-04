#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void main(int argc,char **argv)
{
	if(argc != 3)	
	{
		printf("Usage : [./a.out] [192.168.1._] [192.168.1._] = ./a.out [ __.__.__.-- ]  [ __.__.__.-- ]\n");
		return;
	}
 
	char str [30] = "ping 192.168.1.";
	int i,j,fd=0;

	i = atoi(argv[1]);
	j = atoi(argv[2]);
//	for(  ; i<256 ; i++)
		for(j = atoi(argv[2]) ; j < 256 ;j++)
		{
			if(!fork())
			{
				close(1);
				fd = open("vurikey",O_APPEND | O_RDWR | O_CREAT,0664);
				sprintf(str,"ping 192.168.1.%d",j);
				system(str);
			}
		}
}

			
