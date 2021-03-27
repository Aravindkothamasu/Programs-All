#include "Huffman_Header.h"



void main (int argc, char **argv)
{  
  char *Ext;
  char OutFileName[150]={0};
  int   InFileDes = -1;
  int   OutFileDes = -1;

  int StartIndex,i;
  sa_data_decode_t **DataPtr;





  CmdLineCheck( argc, 2);
  CheckFile( argv[1]);



  InFileDes = FileOpening( argv[1], READ_MODE_FILE);

  CreateOutFileName( OutFileName, argv[1]);

  strcat( OutFileName, "_Tmp");             //TODO : Remove after testing
  console_print("I/p FileName : %s\n", argv[1] );
  console_print("O/p FileName : %s\n", OutFileName);

  OutFileDes = FileOpening( OutFileName, WRITE_MODE_FILE);


  StartIndex = GetCountDS( InFileDes);

  if( StartIndex < 0)
  {
    console_print("Error in Reading Binary Data\n");
    return;
  }
  else
    console_print("StartIndex : %d\n", StartIndex);

  DataPtr = calloc( sizeof( sa_data_decode_t), StartIndex);

  if( NULL != DataPtr )
  {
    for( i=0;i<StartIndex;i++)
    {
      DataPtr[i] = malloc( sizeof(sa_data_decode_t));

      switch( ReadDS( DataPtr[i], InFileDes) )
      {
        case 0:
          //console_print("Read Data Not Matched\n");

          break;
        case 1:
          console_print("%3d Data : %X EncData : %X Bit : %X\n", i,
              DataPtr[i]->Type, DataPtr[i]->EncData, DataPtr[i]->BitOfEnc);

          break;
        case 2:


          break;
      }
    }
  }
  else
  {
    console_print("Calloc Failed : %s\n", strerror(errno));
    return;
  }

}

uint8_t ReadDS(sa_data_decode_t *Ptr, int FileDes)
{
  uint8_t Data[7]={0};

  if( -1 == read( FileDes, Data, sizeof(Data)) )
  {
    console_print("Unable to Read the file : %s\n", strerror(errno));
    return 2;
  }
  else
  {
    console_print("Data Read Ds : %X %x %x %x %x %x %x\n",
        Data[0],
        Data[1],
        Data[2],
        Data[3],
        Data[4],
        Data[5],
        Data[6]);

    if( Data[0] != DATA_ST_BYTE_0 )
      return 0;
    if( Data[1] != DATA_ST_BYTE_1 )
      return 0;
    if( Data[5] != DATA_ST_BYTE_5 )
      return 0;
    if( Data[6] != DATA_ST_BYTE_6 )
      return 0;

    Ptr->Type     = Data[2];
    Ptr->EncData  = Data[3];
    Ptr->BitOfEnc = Data[4];

  }
  return 1;
}


int GetCountDS( int FileDes)
{
  console_print("Decode Func Called\n");

  uint8_t DataRead[5]={0};
  int Iterator=0;


  console_print(" Read File Des : %d\n", FileDes);

  if( -1 == read( FileDes, DataRead, sizeof(DataRead)) )
  {
    console_print("Read Called Failed : %s\n", strerror(errno));
    return -1;
  }

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


void CreateOutFileName ( char *OutFileName, char *InFileName)
{
  console_print("Create Out FileName Func Called\n");

  int Len = strlen( InFileName );
  strncpy( OutFileName, InFileName, Len - 4);
  console_print("Out FileName : %s\n", OutFileName);


}  

void CheckFile( char *FileName)
{
  char temp[5] = ".bin";
  char TempFileName[150]={0};
  int len = 0,i;


  strcpy( TempFileName, FileName);
  len = strlen( FileName) -1;

  for( i=0;i<4;i++)
    if( temp[i] != FileName[len-3+i] )
    {
      console_print("Input FileName externtion is not ended with .bin\n");
      exit(0);
    }
}


