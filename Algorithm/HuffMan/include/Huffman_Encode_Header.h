#ifndef __HUFFMAN_ENCODE_HEADER_H__
#define __HUFFMAN_ENCODE_HEADER_H__


#include"Huffman_Header.h"


#define PRINT_CURRENT_BUF_POSITION( Text, Data, EncData, BitOfEnc, BinDataWrIndex, BinDataBuf )   \
    console_print( LOG_PRIO_1, "%s ASCII: %2X EncD: %2X BitEnc %2d || WrIndx : %02d  Bin : %s\n", Text, Data,\
	EncData, BitOfEnc, BinDataWrIndex, \
	GetBinaryInArray(BinDataBuf, ENCODE_BUF_BYTES, Buffer));


#define APPEND_BIT( BinDataBuf, BinDataWrIndex, Bit, MaxLen )	\
{ \
  BitFeed( BinDataBuf, BinDataWrIndex, Bit); \
  DECCIRCULARINDEX( BinDataWrIndex, ENCODE_BUF_BITS_LEN );  \
}


#define	      ENCODE_BUF_BYTES			  8
#define	      ENCODE_BUF_BITS_LEN	  ENCODE_BUF_BYTES * 8



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
  uint8_t data;
  int freq;
}as_bst_t;


typedef struct 
{
  int		    InFileDes;
  int		    OutFileDes;

  int		    StartIndex;
  as_bst_t	    *root;

  off_t		    OutFdLastBitPostion;
  uint64_t	    InFileBytesRead;
  uint64_t	    SrcFileSizeInBytes;
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




//////////////////	  ENCODE.C    ///////////////////

// void CopyBuffer(as_huff_t *);
// bool ParseInputData (as_huff_t *);
// void ArrangeAssendingOrder(as_huff_t*);



void ReadInputFile(int );
void RearrangeData();
void swap(int i, int j);
int GetStartingPoint();
bool CreateArray( uint8_t, uint64_t , int, int);
bool WriteInToFile(int , int );
void WriteRemaingData( int );
void CreateOutFileName( char *, char *);
void Fooder(int );
void Header( int );
void WriteFileSize( as_huff_t *, uint64_t );
void PrintPercentageFileRead( as_huff_t *);
void ClosingCeremony(  as_huff_t *, char* );

/*	  META DATA FUNCTIONS	  */
void WriteMetadata ( as_huff_t *HuffPtr );
int CalculateSourceFile( as_huff_t *);
void WriteCountDS ( as_huff_t *);
void CreateDSFrame( as_huff_t *);
void WriteLastBitIndex( as_huff_t *, uint8_t );



//////////////////	  GREEK.C    ///////////////////

uint64_t MaskRemBits ( uint64_t , int );
uint64_t ReverseBits ( uint64_t , int );
struct MinHeapNode *  HuffmanCodes( int );
void PrintArrBin ( as_data_t );



//////////////////	  BST.C    ///////////////////
#if 0
void createBST( as_huff_t  *);
void CreateNewNode(as_bst_t **,char ,int );
int * filter( as_bst_t *root, char *);
#endif




#endif
