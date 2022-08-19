#ifndef __HUFFMAN_DECODE_HEADER_H__
#define __HUFFMAN_DECODE_HEADER_H__

#include"Huffman_Header.h"









#define	      MAX_DATA_CAN_READ		100
#define	      DECODE_MAX_LEN_BUF_LEN	10


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

#if 0
  DEC_FILE_SIZE		    ,
  DEC_DS_COUNT		    ,
  DEC_ALLOCATE		    ,
  DEC_GET_DS		    ,
#else
  DEC_ENCRYPT_METADATA	    ,
#endif

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
  uint64_t  Data;
  uint8_t   EnnoBit;
  uint8_t   Ennodhi;


}Huff_Dec_Prev_St;


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
  uint8_t	        LastBitPos;

  Huff_Decode_DataStru_t **DataPtr;
  int			  Indx;

  Huff_Decode_DataFlow_t  DataFlowSt;
  Huff_Decode_State_t	  MainSt;
  Huff_Decode_Metadata_t  MetadataSt;

  Huff_Dec_Prev_St	  Prev;

  uint64_t		SrcFileSizeInBytes;


  uint8_t		  OutFileBuf[DECODE_MAX_LEN_BUF_LEN];
  int			  OutFileBufIndex;

}Huff_Decode_app_t;



//////////////////	  DECODE.C    ///////////////////

void CreateOutFileName( char *, char *);
void CheckIpFile( char *);
void CreateOutFileName ( char *, char *);     // TODO : Need to Change in encode.c and decode.c files
int GetCountDS( uint8_t , int * );
bool MapData( Huff_Decode_app_t *, uint8_t, int);
bool CheckEncode( bool , uint8_t *);
bool AllocateMainMem( Huff_Decode_DataStru_t ***, int );
int ReadData( Huff_Decode_app_t *);
void PrcsIpData( Huff_Decode_app_t *, uint8_t );
void PrintDSdata(  Huff_Decode_app_t  * );
bool AllocateSubMemory( Huff_Decode_DataStru_t ***, int );
void DecodeHuffMan(Huff_Decode_app_t *, int , char **);
void WriteData( Huff_Decode_app_t *);
bool GetSourceFileSize( uint8_t , uint64_t * );
int ReadMetaData( Huff_Decode_app_t *, uint8_t );
void MemoryAllocation( Huff_Decode_DataStru_t ***, int );
void ReadLastBitPostion( uint8_t *);


void AppendData(Huff_Decode_app_t *AppPtr );
void Decode_ParseData( Huff_Decode_app_t *, uint64_t *, int *, int *);



// uint8_t ReadDS( Huff_Decode_DataStru_t *, int );
// char * GetOutFileExtent( int , char *);





#endif
