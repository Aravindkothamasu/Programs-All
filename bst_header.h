

#ifndef __BST_HEADER_H__
#define __BST_HEADER_H__
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>


typedef struct base
{
	struct base *parent;
	struct base *left;
	struct base *right;
	int num;
}B;
char input(int *); 
void print(B *);
int * filter (B** ,int );
void create(B **,int);

#endif
