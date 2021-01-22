#include"header.h"
void main(int argc,char **argv) 
{ 
	if(argc!=2) 
	{ 
		printf("./a.out file name\n"); 
		return; 
	} 
	sou = open(argv[1],O_RDONLY); 
	if(sou < 0) 
	{ 
		perror("open"); 
		return; 
	} 
	copy_fil(argv[1]); 
	check(argv[1]);
	printf("slash..head\n");
	slash_star("hddr","hddr1");
	printf("doub..head\n");

	double_slash("hddr1","hddr2");
	printf("slash star file\n");
	slash_star("1111","2222"); 
	printf("double slash file\n");
	double_slash("2222","3333"); 
} 

