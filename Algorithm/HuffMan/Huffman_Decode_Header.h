#ifndef __HUFFMAN_DECODE_HEADER_H__
#define __HUFFMAN_DECODE_HEADER_H__

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


  Huff_Decode_DataStru_t **DataPtr;
  int			  Indx;

  Huff_Decode_DataFlow_t  DataFlowSt;
  Huff_Decode_State_t	  MainSt;

  Huff_Dec_Prev_St	  Prev;

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
bool GetBitVal( uint64_t, uint8_t );
void WriteData( Huff_Decode_app_t *);




#endif
