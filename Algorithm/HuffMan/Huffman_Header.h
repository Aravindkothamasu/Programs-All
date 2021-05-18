

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

#define MAX_LEN_BUF_BITS    63

#define SIZE_BUFFER 10
#define READ_MODE_FILE	      O_RDONLY
#define WRITE_MODE_FILE	      O_RDWR|O_TRUNC|O_CREAT

#define TOT_CHARS	      0x7f

#define DEBUG_ON_ENCODE		0
#define DEBUG_ON_DECODE		1

#define console_print( format, ...)	      \
    FramingData( __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 

#define CAL_SIZE(a)   (0x7f - a +1 )

typedef struct 
{
  uint64_t    EncData;
  uint8_t    BitOfEnc; 
  uint8_t     Type;
  uint32_t     Freq;

}as_data_t;

typedef struct myBst
{
  struct myBst *left,*right,*parent;
  unsigned long int Sum;
  uint8_t data;
  int freq;
  bool LorR;
}as_bst_t;

typedef struct 
{
  char *characters;
  char *Backup;
  int *CountOfEachChar;
  int TotChar;
  int InFileDes;
  int OutFileDes;
  int StartIndex;
  as_bst_t *root;
}as_huff_t;


struct MinHeapNode {
  char data;
  unsigned freq;
  struct MinHeapNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHeapNode** array;
};


void CopyBuffer(as_huff_t *);
bool ParseInputData (as_huff_t *);
void ArrangeAssendingOrder(as_huff_t*);
int FileOpening (char *,short int);
void FramingData( int , const char *, const char *, const char *, ...);
void ReadInputFile(int );
void RearrangeData();
void swap(int i, int j);
int GetStartingPoint();
bool CreateArray(uint8_t , int, int);
void CreateDSFrame( as_huff_t *);
bool WriteInToFile(int );
uint64_t MaskRemBits ( uint64_t , int );
uint64_t ReverseBits ( uint64_t , int );
bool WriteDataIntoFile( as_huff_t *, uint8_t *, int );
void WriteCountDS ( as_huff_t *);




//*******************************************//
void createBST( as_huff_t  *);
void CreateNewNode(as_bst_t **,char ,int );
//int * filter( as_bst_t *root, char *);
//*******************************************//
struct MinHeapNode *  HuffmanCodes( int );
char * GetBinary (uint64_t  ,int , char *);
uint8_t MaskData(uint8_t );
int CheckDiff();
void CmdLineCheck(int , int );
void CreateOutFileName( char *, char *);

void Fooder(int );
void Header( int );
void PrintDataStruct ( struct MinHeapNode *, as_huff_t *);

void WriteRemaingData( int );




///////////////////////     DECODE.C      /////////////////////



#define MAX_DATA_CAN_READ   100

typedef enum
{
  DS_HDDR_STR_1	   = 0,
  DS_HDDR_STR_2    = 1,
  DS_DATA_TYPE     = 2,
  DS_DATA_BIT_ENC  = 3,
  DS_DATA_ENC_DATA = 4,
  DS_DATA_FOOT_1   = 5,
  DS_DATA_FOOT_2   = 6,

}Huff_Decode_DataFlow_t;


typedef enum 
{
  DEC_CHCK_IN_FILE	    ,
  DEC_IN_FILE		    ,
  DEC_CREATE_OUT_FILENAME   ,
  DEC_OPEN_OUTFILE	    ,
  DEC_DS_COUNT		    ,
  DEC_ALLOCATE		    ,
  DEC_GET_DS		    ,
  DEC_HEADER		    ,
  DEC_MAP_DATA		    ,
  DEC_FOOTER		    ,
  DEC_SENDOFF		    ,

}Huff_Decode_State_t;


typedef struct 
{
   uint64_t EncData;
   uint8_t BitOfEnc;
   uint8_t Type;

}Huff_Decode_DataStru_t;

typedef struct
{
  int                    InFileDes;
  int                   OutFileDes;
  int                   CountIndex;


  char                  OutFileName[150];

  
  uint8_t		IpData[ MAX_DATA_CAN_READ];
  uint8_t		OpData[ MAX_DATA_CAN_READ];
  int			RdRtnBytes;
  int			WritePtr;


  Huff_Decode_DataStru_t **DataPtr;
  int			  Indx;

  Huff_Decode_DataFlow_t  DataFlowSt;
  Huff_Decode_State_t	  MainSt;




  int			LastIndx;
  int			LastBit;
}Huff_Decode_app_t;


void CheckIpFile( char *);
void CreateOutFileName ( char *, char *);
uint8_t ReadDS( Huff_Decode_DataStru_t *, int );
char * GetOutFileExtent( int , char *);
int GetCountDS( Huff_Decode_app_t * );
bool MapData( Huff_Decode_app_t *, uint8_t);
bool CheckEncode( bool , uint8_t *);
bool AllocateMainMem( Huff_Decode_app_t *);
void ReadData( Huff_Decode_app_t *);
bool PrcsIpData( Huff_Decode_app_t *, uint8_t );
bool AllocateSubMemory( Huff_Decode_app_t *);
void DecodeHuffMan(Huff_Decode_app_t *, int , char **);
void PrintDSdata(  Huff_Decode_app_t  * );
bool GetBitVal( uint64_t , uint8_t );
void WriteData( Huff_Decode_app_t *);





#endif
