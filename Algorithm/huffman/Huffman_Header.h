

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


#define console_print( format, ...)	      \
    FramingData( __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 

#define CAL_SIZE(a)   (0x7f - a +1 )

typedef struct 
{
  int Freq;
  char Type;
  int top;
  char data[10];

  uint8_t    EncData;
  uint8_t    BitOfEnc; 

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
int FileOpening (char *,int);
void FramingData( int , const char *, const char *, const char *, ...);
void ReadInputFile(int );
void RearrangeData();
void swap(int i, int j);
int GetStartingPoint();
bool CreateArray(uint8_t , int, int);
bool WriteInToFile(int );




//*******************************************//
void createBST( as_huff_t  *);
void CreateNewNode(as_bst_t **,char ,int );
//int * filter( as_bst_t *root, char *);
//*******************************************//
struct MinHeapNode *  HuffmanCodes( int );
char * Binary (uint64_t  a,int size_in_bytes)	;
uint8_t MaskData(uint8_t );
int CheckDiff();
int CmdLineCheck(int );
void CreateOutFileName( char *, char *);

void Fooder(int );
void Header( int );

void WriteRemaingData( int );

#endif
