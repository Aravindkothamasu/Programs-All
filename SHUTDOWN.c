#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include<errno.h> 
#include<string.h>

void Control_C(int sig)
{
	printf("\n\n\t\t\t aa Pappullu ekada kudaravu...\n\n");
}
void Termination(int sig)
{
	printf("\n\t\t\t Exiting from program...\n");
	sleep(1);
	exit(0);
}
void main(int argc,char **argv)
{	
	if(argc != 3)
	{
		printf("\n\n\t\t\t|-----------------------------------------|\n");
		printf("\t\t\t|  Usage [*.executable_file] [min] [sec]  |\n");
		printf("\t\t\t|-----------------------------------------|\n\n\n");
		return;
	}
	if(!fork())								//9,20,2,15,19,10
	{
		unsigned int i=0,j,k=0,l=0,fd=0;
	/*	struct sigaction a = {0};
		//bzero(a,&a);
//		sigemptyset(&a.sa_mask);
		a.sa_restorer = SIG_IGN;
		a.sa_sigaction = Control_C;
		a.sa_flags = SA_SIGINFO;
//		a.sa_handler = Control_C;
		if (sigaction(SIGKILL,&a,NULL) == -1)
		{
			printf("Setting sigaction fails...\n");
			printf("%d : %s\n",errno,strerror(errno));
			return;	
		}		*/

		printf("\n\n\t\t***** Program to shutdown *****\n\n\n");

		usleep(1500);
		printf("\n\n\npid = %d \n",getpid());
		for(k = (atoi(argv[1])*60)+(atoi(argv[2])) ; k>0 ; k--)
		{	

			printf("\t\tSystem is shutting down in : %d sec's \r",k+1);
			for(i=0,j=~i/10;i<j;i++);	
			fflush(stdout);		
			if(k == 3)
			{
//				fd = dup(1);
//				close(1);				
				printf("\n\n\t\t*************  bye  **********\n");	
				sleep(1);
				system("poweroff");
				/*dup2(fd,1);
				close(fd);*/
			}
		}
	
	}
	else	
		exit(0);
}
