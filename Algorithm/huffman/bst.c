
#include"Huffman_Header.h"


void createBST(as_huff_t *HuffMan)
{
  int i;
  for(i=0;i<HuffMan->TotChar;i++)
    CreateNewNode( &(HuffMan->root), HuffMan->characters[i], HuffMan->CountOfEachChar[i]);
}

void CreateNewNode(bst_t **root,char data,int Repeat)
{
  bst_t *p;
  if( *root == NULL )
  {   
    *root = calloc(1,sizeof(bst_t));
    if( *root == NULL)
      exit(0);
    (*root)->data      = data;
    (*root)->Sum = (*root)->freq = Repeat;
    (*root)->parent    = NULL;
  }
  else
  {
    p = calloc(1,sizeof(bst_t));
//    p->parent = filter(*root,data);
  //  if (p->parent->Sum < Repeat)


  }
}

/*
int * filter(bst_t *root,char *data)                                  //Rtn Daddie of it
{



}
*/
