#ifndef __HUFFMAN_ENCODE_HEADER_H__
#define __HUFFMAN_ENCODE_HEADER_H__


#include"Huffman_Header.h"

#define DEBUG_ON_ENCODE_PRINT	    0


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




//////////////////	  ENCODE.C    ///////////////////

// void CopyBuffer(as_huff_t *);
// bool ParseInputData (as_huff_t *);
// void ArrangeAssendingOrder(as_huff_t*);



void ReadInputFile(int );
void RearrangeData();
void swap(int i, int j);
int GetStartingPoint();
bool CreateArray( uint8_t, uint64_t , int, int);
void CreateDSFrame( as_huff_t *);
bool WriteInToFile(int );
bool WriteDataIntoFile( as_huff_t *, uint8_t *, int );
void WriteCountDS ( as_huff_t *);
uint8_t MaskData(uint8_t );
int CheckDiff();
void WriteRemaingData( int );
void CreateOutFileName( char *, char *);
void Fooder(int );
void Header( int );
void WriteMetadata ( as_huff_t *HuffPtr );
int CalculateSourceFile( as_huff_t *);
void WriteFileSize( as_huff_t *, uint64_t );





//////////////////	  GREEK.C    ///////////////////

uint64_t MaskRemBits ( uint64_t , int );
uint64_t ReverseBits ( uint64_t , int );
struct MinHeapNode *  HuffmanCodes( int );



//////////////////	  BST.C    ///////////////////
#if 0
void createBST( as_huff_t  *);
void CreateNewNode(as_bst_t **,char ,int );
int * filter( as_bst_t *root, char *);
#endif




#endif