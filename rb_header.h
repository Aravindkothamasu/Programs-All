

#ifndef __RB_HEADER_H__
#define __RB_HEADER_H__
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<unistd.h>
typedef struct base
{
	struct base *parent;
	struct base *left;
	struct base *right;
	int flag;					//RED or  BLACK
	int num;
}B;
char input(int *); 
void Parsing(int ,char **,B **);
int height(B *);

int * filter (B *,int,int );
void create(B **,int);
int check(B*);

int search(B **,int );
void deletion(B **,int );


void rotation(B **,B **);
void Rrotate(B *,B**);
void Lrotate(B *,B**);



void OnlyAdd(B **);
void PrintAddr(B **);


void Flag_print(B *);
void print(B *);
#endif
