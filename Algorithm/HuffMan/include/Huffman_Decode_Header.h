#ifndef __HUFFMAN_DECODE_HEADER_H__
#define __HUFFMAN_DECODE_HEADER_H__

#include "Huffman_Header.h"

#define	      DECODE_IN_BUF_MAX_LEN		1000

#define	      DECODE_OUT_BUF_MAX_LEN		1000
#define	      DECODE_BUF_BYTES			  12
#define	      DECODE_BUF_BITS_LEN	  DECODE_BUF_BYTES * 8



/*	  DECODE  STATEFLOW DECLERATION	  */

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



/*	  DECODE METADATA STATEFLOW DECLERATION	  */

typedef enum
{
  METADATA_FILE_SIZE		    ,
  METADATA_COUNT_DS		    ,
  METADATA_READ_DS		    ,
  METADATA_LAST_BIT		    ,

}Huff_Decode_Metadata_t ;





/*	  DECODE MAIN STATE FLOW DECLERATION	  */

typedef enum 
{
  DEC_CHCK_IN_FILE	    ,
  DEC_IN_FILE		    ,
  DEC_CREATE_OUT_FILENAME   ,
  DEC_OPEN_OUTFILE	    ,
  DEC_ENCRYPT_METADATA	    ,
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
  int                   InFileDes;
  int                   OutFileDes;
  int                   CountIndex;

  char                  OutFileName[150];

  
  uint8_t		IpData[ DECODE_IN_BUF_MAX_LEN ];
  int			RdRtnBytes;
  uint8_t	        LastBitPos;

  Huff_Decode_DataStru_t **DataPtr;
  int			  Indx;

  Huff_Decode_DataFlow_t  DataFlowSt;
  Huff_Decode_State_t	  MainSt;
  Huff_Decode_Metadata_t  MetadataSt;

  uint64_t		  SrcFileSizeInBytes;
  uint64_t		  OutFileWrittenBytes;

  uint8_t		  OutFileBuf[ DECODE_OUT_BUF_MAX_LEN ];
  int			  OutFileBufIndex;

  uint64_t		  EncryptFileSize;
  uint64_t		  EncryptFileCount;
}Huff_Decode_app_t;



//////////////////	  DECODE.C    ///////////////////

void DecodeHuffMan(Huff_Decode_app_t *, char *);

void CreateOutFileName( char *, char *);
void CheckIpFile( char *);
void CreateOutFileName ( char *, char *);     // TODO : Need to Change in encode.c and decode.c files
int GetCountDS( uint8_t , int * );
bool MapData( Huff_Decode_app_t *, uint8_t, int);
bool CheckEncode( bool , uint8_t *);
bool AllocateMainMem( Huff_Decode_DataStru_t ***, int );
int ReadDataIpSrcFile( Huff_Decode_app_t *);
void PrcsIpData( Huff_Decode_app_t *, uint8_t );
void PrintDSdata(  Huff_Decode_app_t  * );
bool AllocateSubMemory( Huff_Decode_DataStru_t ***, int );
void WriteData( Huff_Decode_app_t *);
bool GetSourceFileSize( uint8_t , uint64_t * );
int ReadMetaData( Huff_Decode_app_t *, uint8_t );
void MemoryAllocation( Huff_Decode_DataStru_t ***, int );
void ReadLastBitPostion( uint8_t *);
void ClosingCeremony(  Huff_Decode_app_t *);
void FreeupMemory( Huff_Decode_app_t *);
void ClearBuffers( Huff_Decode_app_t *);


void AppendData(Huff_Decode_app_t *AppPtr );
void Decode_ParseData( Huff_Decode_app_t *, uint8_t *, int *, int *);
uint64_t DATA_BUF( uint8_t *, int );
void PrintPercentageFileRead( Huff_Decode_app_t *);



#endif
