///////////////////////HEADER_RAIN.h////////////////////////////////


#ifndef __HEADER_RAIN_H_
#define __HEADER_RAIN_H_

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<strings.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

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


/*         new.c    */ 

void ReDistribute(ak_data* ,ak_int );
void ReArrange(ak_data *,ak_int );
void Maths(ak_data* ,ak_int ,ak_int ,ak_int );
void Non_Lag(ak_data* ,ak_int ,ak_int );
ak_int SideBlockIp(ak_int);
void Panchadam(ak_data*,ak_int ,ak_int);
int Distribute(ak_data *,ak_int,ak_int );
ak_int Occupy(ak_data *);
ak_int Vennaka(ak_int );
void NextNode(ak_data **);		
ak_int NextNum(ak_data*);


///////////////////////////////////////
/*              support.c             */
ak_int CmdLineParse(ak_int ,ak_char**);
void SmallHelp(void);
void developer(void);
void readme(void);
void Help(void);
ak_char* version(void);


///////////////////////////////////////
/*              support.c             */
ak_data * LastNode(ak_data * );
ak_int start(void);
void create(ak_data **,ak_int,ak_int );
void PrintAddr(ak_data*);
ak_data * AddEnd(ak_data*);
ak_data * SecondHalf(ak_data *);
void my_Print(ak_data*);
void Print(ak_data*,ak_int );
ak_int input(int);	


#endif
