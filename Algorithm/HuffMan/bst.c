
#include"Huffman_Header.h"
extern as_data_t CountData[TOT_CHARS+1];

void createBST(as_huff_t *HuffMan)
{
  int i;
  for(i=HuffMan->StartIndex ;i<=TOT_CHARS;i++)
    CreateNewNode( &(HuffMan->root), HuffMan->characters[i], HuffMan->CountOfEachChar[i]);
}

void CreateNewNode(as_bst_t **root,char data,int Repeat)
{
  as_bst_t *p;
  if( *root == NULL )
  {   
    *root = calloc(1,sizeof(as_bst_t));
    if( *root == NULL)
      exit(0);
    (*root)->data      = data;
    (*root)->Sum = (*root)->freq = Repeat;
    (*root)->parent    = NULL;
  }
  else
  {
    p = calloc(1,sizeof(as_bst_t));
//    p->parent = filter(*root,data);
  //  if (p->parent->Sum < Repeat)


  }
}

/*
int * filter(as_bst_t *root,char *data)                                  //Rtn Daddie of it
{



}
*/
