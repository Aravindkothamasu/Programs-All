/////////////////////////////////HEADER.h///////////////////////////////////////////////////

#ifndef __RB_HEADER_H__
#define __RB_HEADER_H__

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

typedef struct base
{
	struct base *parent;
	struct base *left;
	struct base *right;
	int flag;						//	-1 D.Black , 0 Black , 1 Red
	int num;
}B;

char input(int *); 
void Parsing(int ,char **,B **);
int height(B *);

void version(void);
int * filter (B *,int,int );
void create(B **,int);
int check(B*);
B* AllRed(B *,B**);

//////////////////////Deletion.c/////////////
void ParsingSibillingRelation(char,B*,B**);
char SibillingStatus(B *);
void SibillingChildBothRBlack(B*,B**);
void RootNodeDelete(B*,B**);




int element(char *);
char NextEnti(B **);
void my_random(B **,int );
void File(B **,char *);
void helpMsg(void);
void string(B **,char *);
void DoSomething(B*,B **,int );
void FilePrint(B *,FILE *);
void FileAddr(B **,FILE *);
void CopytoFile(B **);
B * Violations(B *,B **,int);
int search(B *,int );
void ReadMe(void);
void deletion(B **,int );
int * Addr_search(B **,int );


B* rotation(B *,B **);


void Rrotate(B *,B**);
void Lrotate(B *,B**);



void OnlyAdd(B **);
void PrintAddr(B **);


void Flag_print(B *);
void print(B *);
void Author(void);
#endif

////////////////////////////////////////////////////////////////////////////////////
