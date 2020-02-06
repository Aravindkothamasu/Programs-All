#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int my_strcmp(char *,char *);
void input(char *,char *);



int a1,a2,b1,b2;

void main(int argc,char **argv)
{
	if(argc != 3)	
	{
		printf("Usage : [./a.out] [192.168.1._] [192.168.1._] = [./a.out] [ __.__.__.-- ]  [ __.__.__.-- ]\n");
		return;
	}	
	input(argv[1],argv[2]);
//	int i = atoi(argv[2]),j = atoi(argv[1]);
	printf("\t\t***********%d*********\n\n\n",getpid());

	for(  ; j <= i  ; j++ )
	{
		if(!fork())
		{
			char str [40],buf[400];
			close(1);
			int Write = open("Temp",O_CREAT | O_WRONLY | O_TRUNC ,0664);
			int Read  = open("Temp",O_RDONLY ,0664);
			int fd = open("vurikay",O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0664);

//			printf("Write = %d Read = %d fd = %d\n",Write,Read,fd);

			if(Write < 0 || Read < 0 || fd < 0)
			{
				printf("*************Error in opening files****************\n\n");
				scanf(" %[^\n]",buf);
				return;
			}

			sprintf(str,"ping -c 2 192.168.1.%d",j);
			//			write(i,str,strlen(str));
			//			write(i,"\n\nARAVIND KOTHAMASU\n\n\n",strlen("\n\nARAVIND KOTHAMASU\n\n\n"));

			if ( system(str) == -1)
			{
				write(i,"system fails \n\n",strlen("system fails \n\n"));

			}
			read(Read,buf,sizeof(buf));


			if( my_strcmp(buf,"ttl=64") == 0 )		
				sprintf(buf,"192.168.1.%d -----------> Ubuntu\n",j);
			else if ( my_strcmp(buf,"ttl=128") == 0 )     
				sprintf(buf,"192.168.1.%d -----------> Windows\n",j);
			else if ( my_strcmp(buf,"ttl=55") == 0 )  
				sprintf(buf,"%s Connected to internet \n",str); 
			else if ( my_strcmp(buf,"ttl=52") == 0 )  
				sprintf(buf,"%s Connected to internet \n",str);
			else   
				sprintf(buf,"192.168.1.%d -----------> Poweroff\n",j);

			write(fd,buf,strlen(buf));

			bzero(str,sizeof(str));
			bzero(buf,sizeof(buf));

			close(Write);
			close(Read);
			close(fd);	
			exit(0);		
		}
		else
		{	
			//system("date");
			//wait(0);
		}

	}
}



int my_strcmp(char *buf,char *p)
{
	int i,j;
	for(i=0;buf[i];i++)
	{
		if( p[0] == buf[i] )
		{
			for(j = 1 ; p[j] ; j++)
				if ( p[j] != buf[i+j] )
					break;

			if ( p[j] == 0 )
				return 0;
		}
	}		
	return -1;
}


void input(char *p,char *q)
{




}
