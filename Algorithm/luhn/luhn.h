#ifndef ___LUHN_H__
#define ___LUHN_H__


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdarg.h>
#include<stdbool.h>
#include<errno.h>
#include<strings.h>
#include<sys/stat.h>
#include<stdint.h>

#define MAX_LEN_NUMBER	  50
typedef struct
{
  uint8_t Data [ MAX_LEN_NUMBER ];
  int	  Len;
}sai_Luhn_t;



#define console_print( format, ...)	      \
    FramingData( __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 





void CheckCmdLineArg( int , char **);
void FramingData( int , const char *, const char *, const char *, ...);
void AnalyzeData( int , char ** );
void PrintData( sai_Luhn_t *);
void ValidateData( sai_Luhn_t *, char **);
bool LuhnAlgorithm( sai_Luhn_t *);
int SumOfDigits( sai_Luhn_t *);


#endif
