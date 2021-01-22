
#ifndef _HEADER_H_
#define _HEADER_H_

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<errno.h>



void copy_fil(char *); 
void slash_star(char *,char*); 
void double_slash(char*,char *); 
int check(char *);
void uhead(char *,int);
void phead(char *,int);
void remove_space(char *);

int sou,dest,flg,star,end; 
char s[350]; 


#endif
