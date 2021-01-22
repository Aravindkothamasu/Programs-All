
#ifndef _HEADER_H_
#define _HEADER_H_
#    include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<dirent.h>

#include<sys/types.h>
#include<sys/stat.h>




void copy_fil(void); 
void slash_star(void); 
void double_slash(void); 
int check(char *);
void uhead(char *,int);
void phead(char *,int);
int sou,dest,i,flg,star,end,j; 
char s[350]; 


#endif
