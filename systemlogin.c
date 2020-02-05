#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
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
 
	char str [40],buf[400];
	int i,j,fd=0;

	j = atoi(argv[1]);
	i = atoi(argv[2]);

	
//	for(  ; i<256 ; i++)
		for(  ; j <= i  ; j++ )
		{
			if(!fork())
			{
				
				int temp = open("Temp",O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC ,0664);
				int fd = open("vurikey",O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0664);
				if(temp < 0 || fd < 0)
				{
					perror("error in opening any of the file.....\n");
					return;
				}

				close(1);
				sprintf(str,"ping -c 3 192.168.1.%d",j);
				system(str);
				read(temp,buf,sizeof(buf));
				
				if(strcmp(buf,"ttl=64") == 0)				
				{
					sprintf(buf,"192.168.1.%d             Ubuntu\n",j);
					write(fd,buf,strlen(buf));
				}				
				else if(strcmp(buf,"ttl=128") == 0)
				{
					sprintf(buf,"192.168.1.%d             Windows\n",j);
					write(fd,buf,strlen(buf));
				}
				close(temp);
				close(fd);
			}
			else
				exit(0);

		}
}

			
