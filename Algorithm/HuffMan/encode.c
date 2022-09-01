
#include "include/Huffman_Encode_Header.h"

as_data_t CountData[TOT_CHARS+1]={0};


uint8_t	   BinDataBuf[ENCODE_BUF_BYTES]	    = {0};
int	   BinDataWrIndex		    =  0;

int	   BytesRead			    =  0;
uint8_t	   ReadBuf[256]			    = {0};



char	   Buffer[1*1024]		    = {0};

float	   PercentageFileRead		    =   0;
int	   LogFileDes			    =  -1;
int	   DebugSt			    =	0;

int main(int argc, char **argv)
{    
  as_huff_t  Huff={0};
  char OutFileName[36]={0};
  int i=0,j;

  uint64_t TempBit = 0;

  CmdLineCheck (argc, 2);

  Huff.InFileDes  = FileOpening(argv[1],  READ_MODE_FILE);

  CreateOutFileName( argv[1], OutFileName);

  BinDataWrIndex  = ENCODE_BUF_BITS_LEN -1;

  Huff.OutFileDes = FileOpening( OutFileName, WRITE_MODE_FILE);
  LogFileDes	  = FileOpening( CreateLogFilename( ENCODE_LOG_DIR_PATH, argv[1] ), WRITE_MODE_FILE );


  for(i=0;i <= TOT_CHARS ;i++)		//For Type Added to 1
    CountData[i].Type = i;

  ReadInputFile(Huff.InFileDes);

  for(i=0 ; i <= TOT_CHARS; i++)
    if( 0 != CountData[i].Freq )
      console_print( LOG_PRIO, "RAW_DATA  -> INDX : %3d || DATA :  %3d || FREQ : %5d\n",
	  i, CountData[i].Type, CountData[i].Freq);

  RearrangeData();
  console_print( LOG_GEN, "\n");

  for(i=0 ; i <= TOT_CHARS ; i++)
    if( 0 != CountData[i].Freq )
      console_print( LOG_GEN, "AFTR_SORT -> INDX : %3d || DATA :  %3d || FREQ : %5d\n",
	  i, CountData[i].Type, CountData[i].Freq);

  Huff.StartIndex = GetStartingPoint();

  if( -1 == Huff.StartIndex )
  { 
    console_print( LOG_ERROR, "Error Occured in Getting StartIndex\n");
    return -1;
  }

  console_print( LOG_GEN,"Start Index : %3d\n",Huff.StartIndex);

  console_print(LOG_GEN, "=====   Creating the Binary Tree  ======\n");
  console_print(LOG_GEN, "\n\n\n");


  HuffmanCodes(Huff.StartIndex);
  console_print(LOG_GEN, "After Creating HuffMan Tree Start Indx : %d CAL : %d\n",
      Huff.StartIndex, CAL_SIZE ( Huff.StartIndex ) );

  for( i = Huff.StartIndex; i <= TOT_CHARS ; i++ )
  {
    TempBit += CountData[i].BitOfEnc;
  }

  console_print(LOG_MAPPING, "\n" );
  console_print(LOG_MAPPING, "\t===========================================\n" );
  console_print(LOG_MAPPING, "\t\t Bit of Enc Tot : %d \n", TempBit);
  console_print(LOG_MAPPING, "\t\t Tot Chars : %d \n", CAL_SIZE( Huff.StartIndex ) * 8 ); 
  console_print(LOG_MAPPING, "\t===========================================\n" );
  console_print(LOG_MAPPING, "\n" );


  /////////////////////////////////////////////////////////////////////////


  if( -1 ==  lseek( Huff.InFileDes, SEEK_SET, 0) )
  {
    close(Huff.InFileDes );
    Huff.InFileDes = FileOpening( argv[1], READ_MODE_FILE);
  }


  ////////////////////// WRITING DATA STRUCTURE INTO .bin FILE  ////////////////////

  WriteMetadata( &Huff );

#if ENCRYPT_HEADER
  Header( Huff.OutFileDes );	      // Writing Headers into OutFile
#endif

  console_print(LOG_GEN, " ============  COMPLETED WRITING DS INTO FILE =============\n");

#if 1
  while( true )
  {
    BytesRead = read( Huff.InFileDes, ReadBuf, sizeof(ReadBuf));

    if( 0 == BytesRead )
    {
      console_print(LOG_GEN, "Reading Done\n");
      break;
    }
    else if( -1 == BytesRead )
    {
      console_print(LOG_ERROR, "Unable to read the input File : %s\n", strerror(errno));
      break;
    }
    else
    {
      Huff.InFileBytesRead  +=  BytesRead;
      PrintPercentageFileRead( &Huff );

      for( i=0 ; i<BytesRead ; i++ )
      {
	for( j = TOT_CHARS; j >= Huff.StartIndex ; j-- )
	{
	  if( ReadBuf[i] == CountData[j].Type)
	  {
	    if( false == CreateArray( CountData[j].Type, CountData[j].EncData, CountData[j].BitOfEnc, Huff.OutFileDes) )
	    {
	      console_print( LOG_ERROR, " ERROR in Creating Frame\n");
	      return -1;
	    }
	    break;
	  }
	}
      }
    }
  }
#endif 
  close( Huff.InFileDes );

  console_print(LOG_MAPPING, "Done OutPut printed on : [ %s ]\n", OutFileName);

#if ENCRYPT_FOOTER
  Fooder( Huff.OutFileDes );
  console_print( LOG_MAPPING, "-------- ENCRYPT Footer Writing Done\n\n");
#else
  console_print( LOG_GEN , "-------- ENCRYPT Footer DISABLED\n\n");
#endif


  ////////// FIXME : Rearrange in a proper manner 
  lseek( Huff.OutFileDes, Huff.OutFdLastBitPostion, SEEK_SET );
  WriteLastBitIndex( &Huff, 5 );
  lseek( Huff.OutFileDes, 0, SEEK_END );
  /////////  


  ClosingCeremony( &Huff, argv[1] );
  return 0;
}


void ClosingCeremony(  as_huff_t *HuffPtr, char *FileName )
{
  struct stat statbuf= {0};

  WriteRemaingData( HuffPtr->OutFileDes);
  if( -1 == fstat( HuffPtr->OutFileDes, &statbuf ))
    console_print( LOG_ERROR, "Getting Properties of OUT FILE ERROR : %s\n", strerror(errno));

  close( HuffPtr->OutFileDes );

  console_print( LOG_MAPPING, "\n");
  console_print( LOG_MAPPING, "=======================================================================\n" );
  console_print( LOG_MAPPING, "==============	  ENCRYPT OF %15s DONE    ==============\n", FileName );
  console_print( LOG_MAPPING, "==============          SOURCE FILE SIZE : %12lld Bytes   =======\n", HuffPtr->SrcFileSizeInBytes );
  console_print( LOG_MAPPING, "==============      COMPRESSED FILE SIZE : %12lld Bytes   =======\n", statbuf.st_size );
  console_print( LOG_MAPPING, "=======================================================================\n" );
  console_print( LOG_MAPPING, "!!!!  No.of Index created : %d   !!!\n", TOT_CHARS - HuffPtr->StartIndex + 1);
  console_print( LOG_MAPPING, "\n\n");

  close( LogFileDes );
  LogFileDes = -1;
}


void WriteMetadata ( as_huff_t *HuffPtr )
{

#if ENCRYPT_FILE_SIZE
  HuffPtr->SrcFileSizeInBytes = CalculateSourceFile( HuffPtr );
  WriteFileSize( HuffPtr, HuffPtr->SrcFileSizeInBytes );
  console_print( LOG_MAPPING,"-------- ENCRYPT File Size Writing DECIMAL : %ld  || HEX : %lX Done\n\n", 
      HuffPtr->SrcFileSizeInBytes, HuffPtr->SrcFileSizeInBytes );
#else
  console_print( LOG_MAPPING,"-------- ENCRYPT File Size DISABLED\n\n");
#endif



#if ENCRYPT_COUNT_DS
  WriteCountDS( HuffPtr );	      // Writing Total Count of Data Structure in File
  console_print( LOG_MAPPING,"-------- ENCRYPT Writing Count DS Done\n\n" );
#else
  console_print( LOG_MAPPING,"-------- ENCRYPT Count DS is DISABLED\n\n");
#endif



#if ENCRYPT_CREATE_DS_FRAME
  CreateDSFrame( HuffPtr );	      // Writing Data Structures Frames into Out File
  console_print( LOG_MAPPING,"-------- ENCRYPT Writing Frame Format Writing Done\n\n");
#else
  console_print( LOG_MAPPING,"-------- ENCRYPT Writing Frame Format DISABLED\n\n");
#endif


  HuffPtr->OutFdLastBitPostion = lseek( HuffPtr->OutFileDes, 0, SEEK_CUR );
  console_print( LOG_MAPPING,"LSEEK POSITION : %d\n", (int ) HuffPtr->OutFdLastBitPostion );

#if ENCRYPT_LAST_BIT_INDEX
  WriteLastBitIndex( HuffPtr, 1 );
  console_print( LOG_MAPPING,"-------- ENCRYPT Writing LAST BIT INDEX Done\n\n");
#else
  console_print( "-------- ENCRYPT Writing LAST BIT INDEX DISABLED\n\n");
#endif
}


void WriteLastBitIndex( as_huff_t *HuffPtr, uint8_t Data )
{
  uint8_t BufWrite[5] = {0};

#if ENCRYPT_LAST_BIT_INDEX
  console_print( LOG_GEN, "Writing Last Bit Index : %d\n", Data );

  BufWrite[0] = ASCII_DLE;
  BufWrite[1] = ASCII_STX;
  BufWrite[2] = Data;
  BufWrite[3] = ASCII_DLE;
  BufWrite[4] = ASCII_STX;

  if( false == WriteDataIntoFile( HuffPtr->OutFileDes, BufWrite, 5) )
    exit( 0 );
#endif

}


int CalculateSourceFile( as_huff_t *HuffPtr )
{
  struct stat statbuf = {0};

  if( -1 == fstat( HuffPtr->InFileDes, &statbuf ))
  {
    console_print( LOG_ERROR,"Unable to get file Properties : %s\n", strerror(errno));
    return 0;
  }

  return ( ( uint64_t ) statbuf.st_size );
}

void WriteFileSize( as_huff_t *HuffPtr, uint64_t FileLenInBytes )
{
  uint8_t     byte_data = 0, Data[12] = {0};
  int	      i, Index	= 0;

  
  Data[Index++] = ASCII_STX;
  Data[Index++] = ASCII_EOT;

  for( i = 7; i >= 0; i-- )
  {
    byte_data	  =  (FileLenInBytes >> ( i * 8 ) ) & 0xFF;
    Data[Index++] =  byte_data; 
  }

  Data[Index++] = ASCII_STX;
  Data[Index++] = ASCII_EOT;


  for( i = 0; i < 12; i++ )
    console_print( LOG_MAPPING,"WRITE FILE SIZE %2d - %02X\n", i, Data[i] );

  if( false == WriteDataIntoFile( HuffPtr->OutFileDes, Data, 12) )
    exit( 0 );
}




void WriteCountDS ( as_huff_t *HuffPtr )
{
  uint8_t BufWrite[7] = {0};

  BufWrite[0] = START_INDEX_BYTE_0;
  BufWrite[1] = START_INDEX_BYTE_1;
  BufWrite[2] = CAL_SIZE( HuffPtr->StartIndex );
  BufWrite[3] = START_INDEX_BYTE_3;
  BufWrite[4] = START_INDEX_BYTE_4;


  if( false == WriteDataIntoFile( HuffPtr->OutFileDes, BufWrite, 5) )
    exit( 0 );
}

void CreateDSFrame( as_huff_t *Huff )
{
  uint8_t i,j=0;
  int k = 0;
  uint8_t BufWrite[20] = {0};

  // DLE-STX TYPE[] BitOfEnc[] EncData[] - DLE-ETX	

  for( i = TOT_CHARS; i >= Huff->StartIndex; i--,j=0 )
  {
    console_print( LOG_MAPPING, "ASCII_DATA : %2X -- BitOfEnc : %2X -- EncData : %X\n", 
	CountData[i].Type, CountData[i].BitOfEnc, CountData[i].EncData );

    memset( BufWrite, 0, sizeof( BufWrite ));

    BufWrite[j++] = DATA_ST_BYTE_0;
    BufWrite[j++] = DATA_ST_BYTE_1;


    BufWrite[j++] = CountData[i].Type;
    BufWrite[j++] = CountData[i].BitOfEnc;

    for( k = CountData[i].BitOfEnc ; k >= 0 ; k -= 8 )	  //FIXME : Need to Cross verify
    {
      BufWrite[j++] = ( CountData[i].EncData >> ( ( k/8 ) * 8 ) ) & 0XFF; 
      //To UnderStand This u need to have master brain
    }

    BufWrite[j++] = DATA_ST_BYTE_5;
    BufWrite[j++] = DATA_ST_BYTE_6;


    if( false == WriteDataIntoFile( Huff->OutFileDes, BufWrite, j) )
      exit( 0 );
  }
}


void CreateOutFileName( char *InFileName, char *OutFileName)
{
  strcpy( OutFileName, InFileName);
  strcat( OutFileName, ".bin");
  return;
}

void testing( int WriteFileDes )
{
  int i;

  for( i = 0x21 ;i<= 0x5a ;i++)
    if ( i >= 0x21 && i<= 0x3f )
    {
      if( false ==  CreateArray( 0, i, 6, WriteFileDes) )
	return;
    }
    else if( i >= 0x40 && i <= 0x4f )
    {
      if( false ==  CreateArray( 0, i, 7, WriteFileDes) )
	return;
    }
    else if( i >= 0x50  )
    {
      if( false ==  CreateArray( 0, i, 7, WriteFileDes) )
	return;
    }
}


void WriteRemaingData( int WriteFileDes)
{
  int ByteCount = 0;
  int temp	= 0;

  for( temp = ENCODE_BUF_BITS_LEN-1; temp >= 0; temp -= 8 )
  {
    ByteCount++;
    // console_print( LOG_ERROR, "temp %2d || ByteCount : %d WRINDX : %d\n", temp, ByteCount, BinDataWrIndex );
    if( temp <= BinDataWrIndex )
      break;
  }

  WriteInToFile( WriteFileDes, ByteCount-1 );
}

void Header( int WriteFileDes)
{

  // STX - EOT - STX - EOT

  CreateArray( 0, ENCODE_HEADER_1, 8, WriteFileDes);
  CreateArray( 0, ENCODE_HEADER_2, 8, WriteFileDes);
  CreateArray( 0, ENCODE_HEADER_3, 8, WriteFileDes);
  CreateArray( 0, ENCODE_HEADER_4, 8, WriteFileDes);
}

void Fooder(int WriteFileDes)
{
  // ETX - ETB - ETX - ETB

  CreateArray( 0, ENCODE_FOODER_1, 8, WriteFileDes);
  CreateArray( 0, ENCODE_FOODER_2, 8, WriteFileDes);
  CreateArray( 0, ENCODE_FOODER_3, 8, WriteFileDes);
  CreateArray( 0, ENCODE_FOODER_4, 8, WriteFileDes);
}


void PrintPercentageFileRead( as_huff_t *HuffPtr )
{
  float FilledUp = 0;

  FilledUp = (float) ( ( HuffPtr->InFileBytesRead * 100 ) / HuffPtr->SrcFileSizeInBytes );

  if( FilledUp != PercentageFileRead )
  {
    PercentageFileRead = FilledUp;

    PrintFillUpData( HuffPtr->SrcFileSizeInBytes, HuffPtr->InFileBytesRead, PercentageFileRead );
  }
}

void ClearBuffers( )
{
  int j;

  BinDataWrIndex = ENCODE_BUF_BITS_LEN -1;
  for( j = 0; j < ENCODE_BUF_BYTES; j++ )
    BinDataBuf[j] = 0;
}

bool CreateArray( uint8_t Data, uint64_t EncData, int BitOfEnc, int WriteFileDes) 
{
  int i, temp;

  if( BinDataWrIndex < BitOfEnc )
  {
    temp = BinDataWrIndex + 1;
    console_print( LOG_PRIO,"CHECK DIFF : %d\n", temp );

    for( i = 0; i < temp; i++ )
    {
      APPEND_BIT( BinDataBuf, BinDataWrIndex, GetBitVal( EncData, BitOfEnc -i-1 ), ENCODE_BUF_BITS_LEN );
    }
    PRINT_CURRENT_BUF_POSITION( "AFT ", Data, EncData, BitOfEnc, BinDataWrIndex, BinDataBuf );

    if( true ==  WriteInToFile( WriteFileDes, ENCODE_BUF_BYTES ))
    {
      ClearBuffers();

      if( BitOfEnc - temp )
      {
	//GET REMAINING DATA
	console_print( LOG_PRIO, "------ REMAINING COUNT : %d\n", BitOfEnc - temp );

	for( i = BitOfEnc-temp; i > 0; i-- )
	{
	  APPEND_BIT( BinDataBuf, BinDataWrIndex, GetBitVal( EncData, i-1 ), ENCODE_BUF_BITS_LEN );
	}
	PRINT_CURRENT_BUF_POSITION( "AWR ", Data, EncData, BitOfEnc, BinDataWrIndex, BinDataBuf );
      }
      else
      {
	console_print( LOG_PRIO, "No Data is Pending to be Written\n" );
      }
    }
    else
    {
      console_print( LOG_ERROR, "Error Writing into file\n");
      return false;
    }
  }
  else
  {
    for( i = 0; i < BitOfEnc; i++ )
    {
      APPEND_BIT( BinDataBuf, BinDataWrIndex, GetBitVal( EncData, BitOfEnc -i-1 ), ENCODE_BUF_BITS_LEN );
    }
  }

  PRINT_CURRENT_BUF_POSITION( "    ", Data, EncData, BitOfEnc, BinDataWrIndex, BinDataBuf );
  return true;
}


bool WriteInToFile(int FileDes, int Bytes )
{
  uint8_t *uPtr8 ;
  int i;

  for( i=0 ;i < Bytes; i++)
  {
    uPtr8 = &(BinDataBuf[ENCODE_BUF_BYTES -1 -i]);
    if( write( FileDes, uPtr8, 1) < 0 )
    {
      console_print( LOG_ERROR, "DATA WRITTEN FAILURE : %s\n", strerror(errno));
      return false;
    }
    else
    {
        // console_print( LOG_GEN, "DATA WRITTEN INTO FILE : %x\n", *uPtr8);
    }
    uPtr8--;
  }
  return true;
}

int GetStartingPoint()
{
  int i=-1;

  for( i=0; i <= TOT_CHARS ;i++)
    if( 0 != CountData[i].Freq )
      return i;
  return i;
}


// FIXME : Re-Look into it.
void RearrangeData()
{
  int i,j;

  for( i=0; i <= TOT_CHARS -1 ; i++)
    for( j=i+1 ; j <= TOT_CHARS ; j++)
    {
      if( CountData[i].Freq > CountData[j].Freq )
      {
	swap(i,j);
      }
    }
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
  uint8_t char_data = 0;
  int i,Len=0;

  while( true )
  {
    bzero(BufRead, sizeof(BufRead));
    Len = read(FileDes, BufRead, sizeof(BufRead));
    if( Len == -1 )
    {
      console_print( LOG_ERROR, "Read Error: %s", strerror(errno));
      break;
    }
    else if( 0 == Len )
      break;

    for( i=0;i<Len;i++)
    {
      char_data = BufRead[i];
      (CountData[ char_data ].Freq)++;
    }
  }
  console_print( LOG_GEN, "Done\n");
}

