

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

#define console_print( format, ...)	      \
    FramingData( __LINE__, __func__, __FILE__, format, ##__VA_ARGS__); 

typedef struct myBst
{
  struct myBst *left,*right,*parent;
  unsigned long int Sum;
  uint8_t data;
  int freq;
  bool side;
}bst_t;

typedef struct 
{
  char *characters;
  char *Backup;
  int *CountOfEachChar;
  int TotChar;
  FILE *InFileDes; 
  FILE *OutFileDes; 
  bst_t *root;
}as_huff_t;


void CopyBuffer(as_huff_t *);
bool ParseInputData (as_huff_t *);
void ArrangeAssendingOrder(as_huff_t*);
void FileOpening (char *,FILE **,char *);
void FramingData( int , const char *, const char *, const char *, ...);




//*******************************************//
void createBST( as_huff_t  *);
void CreateNewNode(bst_t **,char ,int );
//int * filter( bst_t *root, char *);
#endif
