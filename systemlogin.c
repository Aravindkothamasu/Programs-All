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
	int i,j,k;
	if(argc != 3)	
	{
		printf("Usage : [./a.out] [192.168.1._] [192.168.1._] = [./a.out] [ __.__.__.-- ]  [ __.__.__.-- ]\n");
		return;
	}	
	input(argv[1],argv[2]);
	printf("\t\t***********%d*********\n\n\n",getpid());

   for( i = a1 , j = b1; i <= a2  ; i++ , j=1 )
	for (  ; ( (i < a2) ? ( (j<254) ? 1 : 0 ) : ( ( j <= b2 ) ? 1  : 0 ) );  j++  )
//	    	 -----------  ////////// --  +++      ```````````  !!!  ^^^^   ......
		if(!fork())
		{
			char str [40],buf[400];
			close(1);
			int Write = open("Temp",O_CREAT | O_WRONLY | O_TRUNC ,0664);
			int Read  = open("Temp",O_RDONLY ,0664);
			int fd = open("vurikay",O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0664);

			if(Write < 0 || Read < 0 || fd < 0)
			{
				printf("*************Error in opening files****************\n\n");
				return;
			}

			sprintf(str,"ping -c 2 192.168.%d.%d",i,j);

			if ( system(str) == -1)
			{
				write(i,"system fails \n\n",strlen("system fails \n\n"));

			}
			read(Read,buf,sizeof(buf));


			if( my_strcmp(buf,"ttl=64") == 0 )		
				sprintf(buf,"192.168.%d.%d -----------> Ubuntu\n",i,j);
			else if ( my_strcmp(buf,"ttl=128") == 0 )     
				sprintf(buf,"192.168.%d.%d -----------> Windows\n",i,j);
			else if ( my_strcmp(buf,"ttl=55") == 0 )  
				sprintf(buf,"%s Connected to internet \n",str); 
			else if ( my_strcmp(buf,"ttl=52") == 0 )  
				sprintf(buf,"%s Connected to internet \n",str);
			else   
				sprintf(buf,"192.168.%d.%d -----------> Poweroff\n",i,j);

			write(fd,buf,strlen(buf));

			bzero(str,sizeof(str));
			bzero(buf,sizeof(buf));

				close(Write);
				close(Read);
				close(fd);	
				exit(0);		
			}
			else;

      printf("\n\n\n\n Check the file [\"vurika\" ] in the same folder\n\n\n");
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
	int i,j;

	for(i=0 ; p[i] != '.' ; i++)
		a1 = a1*10+p[i]-48;
	for(i++; p[i];i++)
		b1 = b1*10+p[i]-48;

	for(i=0;q[i] != '.';i++)
		a2 = a2*10+q[i]-48;
	for(i++; q[i] ; i++)
		b2 = b2*10+q[i]-48;
}
