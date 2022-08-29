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
#include<sys/time.h>
#include<stdint.h>
#include<time.h>


////////////////////////     LOGS DIRECTORY MACRO DECLERATION	    /////////////////////////

#define	    ENCODE_LOG_DIR_PATH	      "logs/Encode/"
#define	    DECODE_LOG_DIR_PATH	      "logs/Decode/"




////////////////////////     ENCRYPT .bin METADATA WRITE PROP	    /////////////////////////

#define	    ENCRYPT_FILE_SIZE		1
#define	    ENCRYPT_COUNT_DS		1
#define	    ENCRYPT_CREATE_DS_FRAME	1
#define	    ENCRYPT_LAST_BIT_INDEX	1

#define	    ENCRYPT_HEADER		1
#define	    ENCRYPT_FOOTER		0




////////////////////////////////////////////////////////



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


#define READ_MODE_FILE	      O_RDONLY
#define WRITE_MODE_FILE	      O_RDWR|O_TRUNC|O_CREAT

#define TOT_CHARS	      0x7f



#define console_print( LogType, format, ...)	      \
    FramingData( LogType, __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 

#define CAL_SIZE(a)   ( TOT_CHARS - a +1 )


#define INCCIRCULARINDEX(Index, Len)  { \
  if(((Index) + 1) >= ((Len)))  \
  (Index) = 0; \
  else \
  (Index)++; \
}


#define DECCIRCULARINDEX(Index, Len)  { \
  if(!Index)  \
  (Index) = Len-1; \
  else \
  (Index)--; \
}


typedef enum
{
  LOG_ERROR	    = 1,
  LOG_MAPPING	    = 2,
  LOG_GEN	    = 3,

  LOG_PRIO	    = 4,

  LOG_SCREEN	    = 5,
}Huff_Debug_Log_St_t;


//////////////////	  COMMON.C    ///////////////////

void CmdLineCheck(int , int );
int FileOpening (char *, short int );
void FramingData( int, int , const char *, const char *, const char *, ...);
char * GetBinary (uint64_t , int , char *);
int Percentage_FillUp( int, int , int );
bool WriteDataIntoFile( int, uint8_t *, int );
bool GetBitVal( uint64_t, uint8_t );
long long GetEpochTimeMs(  );

void BitFeed( uint8_t *, int , bool );
void BitClear( uint8_t *, int, int );
void BitSet( uint8_t *, int, int );

char * GetBinaryInArray (uint8_t *,int , char *);
bool GetBitValInArray( uint8_t *, int );
void PrintFillUpData( int , int , float );
char * CreateLogFilename( char *, char *);
void ProgramExit( bool );
void WriteLogFile( int , int , char *, int );




#endif
