#ifndef __HUFFMAN_HEADER_H__
#define __HUFFMAN_HEADER_H__

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



#define ASCII_DLE	 0X10
#define ASCII_STX	 0X02
#define ASCII_ETX	 0X03
#define ASCII_EOT	 0x04
#define ASCII_ETB	 0x17
#define ASCII_SOH	 0x01
#define ASCII_EM	 0x19


#define START_INDEX_BYTE_0    ASCII_DLE
#define START_INDEX_BYTE_1    ASCII_SOH
#define START_INDEX_BYTE_3    ASCII_DLE
#define START_INDEX_BYTE_4    ASCII_EM

#define DATA_ST_BYTE_0	    ASCII_DLE
#define DATA_ST_BYTE_1	    ASCII_STX
#define DATA_ST_BYTE_5	    ASCII_DLE
#define DATA_ST_BYTE_6	    ASCII_ETX


////////////////////////////////////////////////////////

#define ENCODE_HEADER_1	     ASCII_STX
#define ENCODE_HEADER_2	     ASCII_EOT
#define ENCODE_HEADER_3	     ASCII_STX
#define ENCODE_HEADER_4	     ASCII_EOT

////////////////////////////////////////////////////////

#define ENCODE_FOODER_1	     ASCII_ETX
#define ENCODE_FOODER_2	     ASCII_ETB
#define ENCODE_FOODER_3	     ASCII_ETX
#define ENCODE_FOODER_4	     ASCII_ETB

////////////////////////////////////////////////////////

#define MAX_LEN_BUF_BITS      63

#define SIZE_BUFFER	      10
#define READ_MODE_FILE	      O_RDONLY
#define WRITE_MODE_FILE	      O_RDWR|O_TRUNC|O_CREAT

#define TOT_CHARS	      0x7f

#define DEBUG_ON_ENCODE		0
#define DEBUG_ON_DECODE		1

#define console_print( format, ...)	      \
    FramingData( __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 

#define CAL_SIZE(a)   (0x7f - a +1 )


#define INCCIRCULARINDEX(Index, Len)  { \
  if(((Index) + 1) >= ((Len)))  \
  (Index) = 0; \
  else \
  (Index)++; \
}






//////////////////	  COMMON.C    ///////////////////

void CmdLineCheck(int , int );
int FileOpening (char *, short int );
void FramingData( int , const char *, const char *, const char *, ...);
char * GetBinary (uint64_t , int , char *);
float Percentage_FillUp( int SlaveId, int WritePtr, int ReadPtr );

#endif
