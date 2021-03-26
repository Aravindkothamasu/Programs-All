#include "Huffman_Header.h"

void main (int argc, char **argv)
{  
  char *Ext;
  int   FileDes = -1;

  CmdLineCheck( argc, 2);
  CheckFile( argv[0]);
  InFileDes = FileOpening( argv[0], READ_MODE_FILE);

  Ext = GetOutFileExtent ( InFileDes, argv[0] );
  OutFileName = CreateOutFileName( Ext, argv[0]);

  FileDes = FileOpening( OutFileName, WRITE_MODE_FILE);

  StartIndex = DecodeDS( InFileDes);

}


int GetCountDS( int FileDes)
{
  console_print("Decode Func Called\n");

  uint8_t DataRead[5]={0};
  int Iterator=0;


  read( FileDes, DataRead, sizeof(DataRead));

  if( START_INDEX_BYTE_0 != DataRead[0]) 
    return -1;
  if( START_INDEX_BYTE_1 != DataRead[1])
    return -1; 
  if( START_INDEX_BYTE_3 != DataRead[3])
    return -1; 
  if( START_INDEX_BYTE_4 != DataRead[4])
    return -1; 

  return DataRead[2];
}

char * GetOutFileExtent( int InFileDes, char *InFileName)
{

  return ;
}


char *GetOutFileExtent (char *BinFileName)
{
  char FileName[256] = {0};


}


void CheckFile( char *FileName)
{
  char temp[5] = ".bin";
  int len = 0;

  len = strlen( FileName) -1;

  for( i=0;i<4;i++)
    if( temp[i] != FileName[len-3+i] )
    {
      console_print("Error in FileName extention : %s\n", FileName);
      exit(0);
    }
}


