///////////////////////HEADER_RAIN.h////////////////////////////////


#ifndef __HEADER_RAIN_H_
#define __HEADER_RAIN_H_

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int ak_int;
typedef char ak_char;
typedef unsigned int ak_uint64;

typedef struct data_structure
{
	ak_int num;
	ak_int flag;					//0->useable,1->star
	ak_int index;					//0-13
	struct data_structure *next;
	struct data_structure *prev;
}ak_data;

void create(ak_data **,ak_int,ak_int );
ak_data * AddEnd(ak_data*);
ak_data * SecondHalf(ak_data *);
ak_data * LastNode(ak_data * );
void PrintAddr(ak_data*);
void Print(ak_data*,ak_int );
ak_int start(void);
void my_Print(ak_data*);
ak_int input(int);	
void Distribute(ak_data*,ak_int ,ak_int );
void ReDistribute(ak_data* ,ak_int );
void ReArrange(ak_data *,ak_int );
void Panchadam(ak_data*,ak_int ,ak_int );
ak_int SideBlockInput(void);
void NextNode(ak_data **);		
ak_int Vennaka(ak_int );
ak_int NextNum(ak_data*);
ak_int Occupy(ak_data *);
ak_int NextNum(ak_data*);
/*
void print(int);
int input(int );
int ReDis(int *,int *,int );
int distribute(int ,int );
int start(void);
*/
#endif



/*	TODO	
 *	print according star based
 *  
 */

///////////////////////////////////////////////////
