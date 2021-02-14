
#include"Huffman_Header.h"

as_data_t CountData[TOT_CHARS+1]={0};
 uint64_t DataToSend = 0;

void main(int argc, char **argv)
{    
  as_huff_t  HuffMan={0};
  struct MinHeapNode *root;
  char FileName[36]={0};
  char *temp;
  uint8_t BufWrite[15] = {0};
  int i=0,j=0;

  if( argc != 2 )
  {   
    console_print("ERROR CMLD LINE USAGE : ./Executable   [Input File]\n");
    return;
  }

  HuffMan.InFileDes  = FileOpening(argv[1],  READ_MODE_FILE);

  console_print("argv[1] : %s\n", argv[1]);

  temp =  strstr( argv[1],".");
  if( NULL == temp)
    HuffMan.OutFileDes = FileOpening(argv[1], WRITE_MODE_FILE);
  else
  {
    strncpy( FileName, argv[1], temp - argv[1] );
    strcat( FileName, ".bin");
    HuffMan.OutFileDes = FileOpening( FileName, WRITE_MODE_FILE);
  }


  if( -1 == HuffMan.InFileDes || -1 == HuffMan.OutFileDes)
    return;

  for(i=0;i<=0x7f ;i++)		//For Type Added to 1
    CountData[i].Type = i;

  ReadInputFile(HuffMan.InFileDes);

  for(i=0 ; i<=0x7f ; i++)
    if( 0 != CountData[i].Freq )
      console_print("%3d, %3d : %5d\n",i, CountData[i].Type, CountData[i].Freq);

  RearrangeData();

  HuffMan.StartIndex = GetStartingPoint();
  if( -1 == HuffMan.StartIndex )
  { 
    console_print("Error Occured in Getting StartIndex\n");
    return;
  }

  console_print("Start Index : %3d\n",HuffMan.StartIndex);

  console_print("=====   Creating the Binary Tree ======\n");


  root = HuffmanCodes(HuffMan.StartIndex);
  console_print("After ReArranging\n");


  for( i = HuffMan.StartIndex; i<=TOT_CHARS; i++ )
  {
    for( j = 0 ; j+CountData[i].data < CountData[i].data+strlen(CountData[i].data) ; j++)
      CountData[i].EncData = ( ( CountData[i].EncData << 1 ) | ( CountData[i].data[j] -48 ) );
    CountData[i].BitOfEnc = j;
  }

  for(i=HuffMan.StartIndex ; i<=TOT_CHARS; i++)
    console_print("%3d, [%3d] Data:%X || Freq: %X || Data:%s || End : %x\n", i,
	CountData[i].top, CountData[i].Type, CountData[i].Freq,
	CountData[i].data, CountData[i].EncData);

  /////////////////////////////////////////////////////////////////////////

    BufWrite[0] = ASCII_DLE;
    BufWrite[1] = ASCII_STX;

    BufWrite[5] = ASCII_DLE;
    BufWrite[6] = ASCII_ETX;

  for ( i = HuffMan.StartIndex ; i <= 0x7f ; i++ )
  {
    BufWrite[2] = CountData[i].Type;  
    BufWrite[3] = CountData[i].EncData;
    BufWrite[4] = CountData[i].BitOfEnc;
    if( 7 != write( HuffMan.OutFileDes, BufWrite,7) )
      console_print("--> %d <-- Write Error : %s\n", i, strerror(errno));
  }


 if( -1 ==  lseek( HuffMan.InFileDes, SEEK_SET, 0) )
 {
    close(HuffMan.InFileDes );
    HuffMan.InFileDes = open(argv[1], READ_MODE_FILE);
    if( -1 == HuffMan.InFileDes )
    {
      console_print("Unable to Open READ file : %s\n", argv[1] );
      return;
    } 
 }

 while( true )
 {
   BytesRead = read( HuffMan.InFileDes, ReadBuf, sizeof(ReadBuf));
   if( 0 == BytesRead )
   {
      console_print("Reading Done\n");
      break;
   }
   else if( -1 == BytesRead )
   {
     console_print("Uable to read the input File : %s\n", strerror(errno));
     break;
   }
   else
   {
      for( i=0 ; i<BytesRead ; i++ )
      {
	for( j=HuffMan.StartIndex ; j<= 0x7f ; j++ )
	  if( ReadBuf[i] == CountData[j].Type)
	  {
	    DataSend( CountData[j].EncData, CountData[j].BitOfEnc, HuffMan.OutFileDes);
	    break;
	  }
      }

   }

 }


  close( HuffMan.InFileDes );
  close( HuffMan.OutFileDes );
}

void DataSend(uint8_t EncData, int BitOfEnc, int OutFileDes)	  //Incomplete
{
 if( No_BitSend+BitOfEnc >= 64 )
 {
  DataToSend = DataToSend >> CountData[j].BitOfEnc |
    CountData[j].EncData;
 }
}

int WriteInToFile()
{


}

int GetStartingPoint()
{
  int i=-1;
  for( i=0;i<=0x7f;i++)
    if( 0 != CountData[i].Freq )
	return i;
  return i;
}

void RearrangeData()
{
  int i,j;
  for( i=0;i<=0x7f-1;i++)
    for( j=i+1 ; j<=0x7f ; j++)
       
      if( CountData[i].Freq  > CountData[j].Freq )
	swap(i,j);
}

void swap(int i, int j)
{
  as_data_t Buff={0};
  Buff = CountData[i];
  CountData[i] = CountData[j];
  CountData[j] = Buff;
}

void ReadInputFile(int FileDes)
{
  char BufRead[200]={0};
  int i,Len=0;

  while( true )
  {
    bzero(BufRead, sizeof(BufRead));
    Len = read(FileDes, BufRead, sizeof(BufRead));
    if( Len == -1 )
    {
      console_print("Read Error: %s", strerror(errno));
      break;
    }
    else if( 0 == Len )
      break;
    for( i=0;i<Len;i++)
      (CountData[BufRead[i]].Freq)++;
  }
  console_print("Done\n");
}

void CopyBuffer(as_huff_t  *HuffMan)
{
  HuffMan->Backup = malloc(sizeof(char)*(HuffMan->TotChar));
  strncpy(HuffMan->Backup,HuffMan->characters,HuffMan->TotChar);
}

void ArrangeAssendingOrder(as_huff_t *HuffMan)
{
  int i,j;
  char temp=0;
  for(i=0;i<(HuffMan->TotChar)-1;i++)
    for(j=i+1;j<(HuffMan->TotChar);j++)
      if( HuffMan->CountOfEachChar[i] > HuffMan->CountOfEachChar[j] )
      {
	HuffMan->CountOfEachChar[i] = HuffMan->CountOfEachChar[j] + HuffMan->CountOfEachChar[i] - (HuffMan->CountOfEachChar[j] = HuffMan->CountOfEachChar[i]);
	temp = HuffMan->characters[i];
      HuffMan->characters[i] = HuffMan->characters[j];
	HuffMan->characters[j] = temp;
      }
}

int FileOpening (char *Filename, int Flags)
{
  int FileDes;
  FileDes = open( Filename, Flags,0664);
  if ( -1 == FileDes )
  {
    console_print("ERROR IN FILE OPENING : %s ,REASON : %s\n",Filename,strerror(errno));
    return -1;
  }
  return FileDes;
}


void FramingData( int Line, const char *Func, const char *File, const char *format, ...)
{								    
  char Buffer[500]={0};
  va_list args;
  va_start( args, format);					    
  sprintf( Buffer, "#%s#  %s() [%d] : ", File, Func, Line);	    
  vsprintf( &Buffer[strlen(Buffer)], format, args);		    
  va_end(args);	
  printf("%s", Buffer);
}

#if 0
bool ParseInputData (as_huff_t  *HuffMan)
{
  bool Gotit=false;
  int i=0;
  char ch=0;

  if ( HuffMan->characters == NULL)
  {   
    HuffMan->characters = calloc(1,sizeof(char));
    if ( HuffMan->characters == NULL)
    {
      console_print("Can't able to allocate memory for characters   %s\n",strerror(errno));
      return false;
    }
    printf("Entered into it\n");
  }

  if( HuffMan->CountOfEachChar == NULL)
  {
    HuffMan->CountOfEachChar = calloc(1,sizeof(int));
    if( HuffMan->CountOfEachChar == NULL )
    {
      console_print("Can't able to allocate memory for CountOfEachChar %s\n",strerror(errno));
      return false;
    }
    printf("Entered...\n");
  }

  (HuffMan->TotChar)++;
  while ( fread(&ch,sizeof(char),1,HuffMan->InFileDes) )
  {
    for(i=0,Gotit=false;i<HuffMan->TotChar;i++)
    {   
      if( ch == HuffMan->characters[i] )
      {
	Gotit = true;
	HuffMan->CountOfEachChar[i]++;
	break;
      }
    }

    if( Gotit == false )
    {
      HuffMan->characters      = realloc(  HuffMan->characters, (HuffMan->TotChar)*sizeof(char));
      HuffMan->CountOfEachChar = realloc(HuffMan->CountOfEachChar,(HuffMan->TotChar)*sizeof(int));
      if(HuffMan->CountOfEachChar == NULL || HuffMan->characters == NULL)
      {
	console_print("ERROR in elocating memory dynamic %s\n",strerror(errno));
	return false;
      }
      else
      {
	HuffMan->CountOfEachChar[(HuffMan->TotChar)-1] = 0;
	HuffMan->characters[(HuffMan->TotChar)-1] = 0;
      }
      HuffMan->characters[(HuffMan->TotChar)-1] = ch;
      (HuffMan->CountOfEachChar[(HuffMan->TotChar)-1])++;
      (HuffMan->TotChar)++;
    } 
  }
  return true;
}
#endif

