

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
}sai_t;


void console_print(char *,...);
void CopyBuffer(sai_t *);
bool ParseInputData (sai_t *);
void ArrangeAssendingOrder(sai_t *);
void FileOpening (char *,FILE **,char *);




//*******************************************//
void createBST(sai_t *);
void CreateNewNode(bst_t **,char ,int );
//int * filter( bst_t *root, char *);
#endif
