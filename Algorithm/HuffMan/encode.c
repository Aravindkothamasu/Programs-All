
#include "include/Huffman_Encode_Header.h"

as_data_t CountData[TOT_CHARS+1]={0};
uint64_t DataToSend = 0;
int BitsOfIndex = 0;

int BytesRead=0;
uint8_t ReadBuf[16] = {0};
char Buffer[128]={0};


int main(int argc, char **argv)
{    
  as_huff_t  Huff={0};
  char OutFileName[36]={0};
  int i=0,j;

  uint64_t TempBit = 0;


  CmdLineCheck (argc, 2);

  Huff.InFileDes  = FileOpening(argv[1],  READ_MODE_FILE);

  CreateOutFileName( argv[1], OutFileName);

  Huff.OutFileDes = FileOpening( OutFileName, WRITE_MODE_FILE);


  for(i=0;i <= TOT_CHARS ;i++)		//For Type Added to 1
    CountData[i].Type = i;

  ReadInputFile(Huff.InFileDes);

#if DEBUG_ON_ENCODE
  for(i=0 ; i <= TOT_CHARS; i++)
    if( 0 != CountData[i].Freq )
      console_print("RAW_DATA  -> INDX : %3d || DATA :  %3d || FREQ : %5d\n",
	  i, CountData[i].Type, CountData[i].Freq);
#endif

  RearrangeData();
  console_print("\n");

#if DEBUG_ON_ENCODE

  for(i=0 ; i <= TOT_CHARS ; i++)
    if( 0 != CountData[i].Freq )
      console_print("AFTR_SORT -> INDX : %3d || DATA :  %3d || FREQ : %5d\n",
	  i, CountData[i].Type, CountData[i].Freq);
#endif

  Huff.StartIndex = GetStartingPoint();

  if( -1 == Huff.StartIndex )
  { 
    console_print("Error Occured in Getting StartIndex\n");
    return -1;
  }

  console_print("Start Index : %3d\n",Huff.StartIndex);

  console_print("=====   Creating the Binary Tree  ======\n");
  console_print("\n\n\n");


  HuffmanCodes(Huff.StartIndex);
  console_print("After Creating HuffMan Tree Start Indx : %d CAL : %d\n",
      Huff.StartIndex, CAL_SIZE ( Huff.StartIndex ) );

  for( i = Huff.StartIndex; i <= TOT_CHARS ; i++ )
  {
    TempBit += CountData[i].BitOfEnc;
  }

  console_print( "\n" );
  console_print( "\t===========================================\n" );
  console_print("\t\t Bit of Enc Tot : %d \n", TempBit);
  console_print("\t\t Tot Chars : %d \n", CAL_SIZE( Huff.StartIndex ) * 8 ); 
  console_print( "\t===========================================\n" );
  console_print( "\n" );


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

  console_print( " ============  COMPLETED WRITING DS INTO FILE =============\n");

#if 1
  while( true )
  {
    BytesRead = read( Huff.InFileDes, ReadBuf, sizeof(ReadBuf));

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
	for( j = TOT_CHARS; j >= Huff.StartIndex ; j-- )
	  if( ReadBuf[i] == CountData[j].Type)
	  {
	    if( false == CreateArray( CountData[j].Type, CountData[j].EncData, CountData[j].BitOfEnc, Huff.OutFileDes) )
	    {
	      console_print(" ERROR in Creating Frame\n");
	      return -1;
	    }
	    break;
	  }
      }
    }
  }
#endif 
  close( Huff.InFileDes );

  console_print("Done OutPut printed on : [ %s ]\n", OutFileName);

#if ENCRYPT_FOOTER
  Fooder( Huff.OutFileDes );
  console_print( "-------- ENCRYPT Footer Writing Done\n\n");
#else
  console_print( "-------- ENCRYPT Footer DISABLED\n\n");
#endif


  ////////// FIXME : Rearrange in a proper manner 
  lseek( Huff.OutFileDes, Huff.OutFdLastBitPostion, SEEK_SET );
  WriteLastBitIndex( &Huff, 5 );
  lseek( Huff.OutFileDes, 0, SEEK_END );
  /////////  

  WriteRemaingData( Huff.OutFileDes);

  close( Huff.OutFileDes );

  console_print("\n");
  console_print("*************   ENCODE OF [%s] DONE    ******************\n", argv[1]);
  console_print("!!!!  No.of Index created : %d   !!!\n", TOT_CHARS - Huff.StartIndex + 1);
  console_print("\n\n");

  return 0;
}



void WriteMetadata ( as_huff_t *HuffPtr )
{

#if ENCRYPT_FILE_SIZE
  uint64_t SrcFileSizeInBytes = 0;

  SrcFileSizeInBytes = CalculateSourceFile( HuffPtr );
  WriteFileSize( HuffPtr, SrcFileSizeInBytes );
  console_print( "-------- ENCRYPT File Size Writing DECIMAL : %ld  || HEX : %lX Done\n\n", 
      SrcFileSizeInBytes, SrcFileSizeInBytes );
#else
  console_print( "-------- ENCRYPT File Size DISABLED\n\n");
#endif



#if ENCRYPT_COUNT_DS
  WriteCountDS( HuffPtr );	      // Writing Total Count of Data Structure in File
  console_print( "-------- ENCRYPT Writing Count DS Done\n\n" );
#else
  console_print( "-------- ENCRYPT Count DS is DISABLED\n\n");
#endif



#if ENCRYPT_CREATE_DS_FRAME
  CreateDSFrame( HuffPtr );	      // Writing Data Structures Frames into Out File
  console_print( "-------- ENCRYPT Writing Frame Format Writing Done\n\n");
#else
  console_print( "-------- ENCRYPT Writing Frame Format DISABLED\n\n");
#endif


  HuffPtr->OutFdLastBitPostion = lseek( HuffPtr->OutFileDes, 0, SEEK_CUR );
  console_print( "LSEEK POSITION : %d\n", (int ) HuffPtr->OutFdLastBitPostion );

#if ENCRYPT_LAST_BIT_INDEX
  WriteLastBitIndex( HuffPtr, 1 );
  console_print( "-------- ENCRYPT Writing LAST BIT INDEX Done\n\n");
#else
  console_print( "-------- ENCRYPT Writing LAST BIT INDEX DISABLED\n\n");
#endif
}


void WriteLastBitIndex( as_huff_t *HuffPtr, uint8_t Data )
{
  uint8_t BufWrite[5] = {0};

#if ENCRYPT_LAST_BIT_INDEX
  console_print( "Writing Last Bit Index : %d\n", Data );

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
    console_print( "Unable to get file Properties : %s\n", strerror(errno));
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
    console_print( "WRITE FILE SIZE %2d - %02X\n", i, Data[i] );

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
    console_print( "ASCII_DATA : %2X -- BitOfEnc : %2X -- EncData : %X\n", 
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

void testing( int FileDes)
{
  int i;

  for( i = 0x21 ;i<= 0x5a ;i++)
    if ( i >= 0x21 && i<= 0x3f )
    {
      if( false ==  CreateArray( 0, i, 6, FileDes) )
	return;
    }
    else if( i >= 0x40 && i <= 0x4f )
    {
      if( false ==  CreateArray( 0, i, 7, FileDes) )
	return;
    }
    else if( i >= 0x50  )
    {
      if( false ==  CreateArray( 0, i, 7, FileDes) )
	return;
    }
}


void WriteRemaingData( int FileDes)
{
  int Bit = 0, i = 0;
  int temp = 0;

  GetBinary( DataToSend, 8, Buffer ); 
  console_print( "BEF %s Data %lX BitIndex %d %s\n", __func__, DataToSend, BitsOfIndex, Buffer );

  /////////////////////////////

  Bit = ( BitsOfIndex / 8 ) + 1;
  console_print( "No.of Bytes : %d Bal %d\n", Bit, Bit * 8 - BitsOfIndex );
  console_print( "Start : %d END : %d\n", Bit*8,  BitsOfIndex );
  temp = BitsOfIndex;

  for( i = Bit*8 ; i > temp; i-- )
  {
    console_print( "-----\n" );
    DataToSend = DataToSend << 1 | 0;
    INCCIRCULARINDEX( BitsOfIndex, MAX_LEN_BUF_BITS );
  }

  /////////////////////////////
  GetBinary( DataToSend, 8, Buffer ); 
  console_print( "BEF %s Data %lX BitIndex %d %s\n", __func__, DataToSend, BitsOfIndex, Buffer );

  WriteInToFile( FileDes, BitsOfIndex/8 );

}

void Header( int FileDes)
{

  // STX - EOT - STX - EOT

  CreateArray( 0, ENCODE_HEADER_1, 8, FileDes);
  CreateArray( 0, ENCODE_HEADER_2, 8, FileDes);
  CreateArray( 0, ENCODE_HEADER_3, 8, FileDes);
  CreateArray( 0, ENCODE_HEADER_4, 8, FileDes);
}

void Fooder(int FileDes)
{
  // ETX - ETB - ETX - ETB

  CreateArray( 0, ENCODE_FOODER_1, 8, FileDes);
  CreateArray( 0, ENCODE_FOODER_2, 8, FileDes);
  CreateArray( 0, ENCODE_FOODER_3, 8, FileDes);
  CreateArray( 0, ENCODE_FOODER_4, 8, FileDes);
}


bool CreateArray( uint8_t Data, uint64_t EncData, int BitOfEnc, int FileDes) 
{
  int i, temp;

  if( BitsOfIndex + BitOfEnc > MAX_LEN_BUF_BITS-1 )
  {
#if DEBUG_ON_ENCODE_PRINT
    console_print("Enter into if \n\n");
    PRINT_CURRENT_BUF_POSITION( "", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
#endif

    temp = CheckDiff();
#if DEBUG_ON_ENCODE_PRINT
    console_print( "CHECK DIFF : %d\n", temp );
#endif

    for( i = 0; i < temp; i++ )
    {
#if DEBUG_ON_ENCODE_PRINT
      console_print( "\n\n" );
      PRINT_CURRENT_BUF_POSITION( "BEF ", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
#endif
      APPEND_BIT( BitsOfIndex, MAX_LEN_BUF_BITS +1, DataToSend, GetBitVal( EncData, BitOfEnc -i-1 ));

#if DEBUG_ON_ENCODE_PRINT
      console_print( "EncData : %X || BitOfEnc %d || BITINDX %d -- BITVALUE %d\n", 
	  EncData, BitOfEnc, BitOfEnc -i -1,
	  GetBitVal( (uint64_t) EncData, BitOfEnc -i -1));

      PRINT_CURRENT_BUF_POSITION( "AFT ", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
      console_print( "\n\n" );
#endif
    }

#if DEBUG_ON_ENCODE_PRINT
    PRINT_CURRENT_BUF_POSITION( "", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
#endif

    if( true ==  WriteInToFile(FileDes, 8))
    {
      BitsOfIndex = DataToSend  = 0;  

      if( BitOfEnc - temp )
      {
	//GET REMAINING DATA
#if DEBUG_ON_ENCODE_PRINT
	console_print( "------ REMAINING COUNT : %d\n", BitOfEnc - temp );
#endif

	for( i = BitOfEnc-temp; i > 0; i-- )
	{
#if DEBUG_ON_ENCODE_PRINT
	  console_print("\n\n" );
	  PRINT_CURRENT_BUF_POSITION( "BWR ", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
#endif

	  APPEND_BIT( BitsOfIndex, MAX_LEN_BUF_BITS, DataToSend, GetBitVal( EncData, i-1 ));

#if DEBUG_ON_ENCODE_PRINT
	  console_print( "EncData : %X || BitOfEnc %d || BITINDX %d -- BITVALUE %d\n", 
	      EncData, BitOfEnc, BitOfEnc -i -1,
	      GetBitVal( (uint64_t) EncData, i -1));

	  PRINT_CURRENT_BUF_POSITION( "AWR ", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
	  console_print( "\n\n" );
#endif
	}
      }
      else
      {
#if DEBUG_ON_ENCODE_PRINT
	console_print( "No Data is Pending to be Written\n" );
#endif
      }
    }
    else
    {
      console_print("Error Writing into file\n");
      return false;
    }

  }
  else
  {
    for( i = 0; i < BitOfEnc; i++ )
    {
      // console_print( "BIT %d EncData : %X BitOfEnc : %d ADDING : %d\n", BitOfEnc -i-1,
      // EncData, BitOfEnc, GetBitVal( ( uint64_t ) EncData, BitOfEnc - i -1 ));
      APPEND_BIT( BitsOfIndex, MAX_LEN_BUF_BITS, DataToSend, GetBitVal( EncData, BitOfEnc -i-1 ));
    }
  }

#if DEBUG_ON_ENCODE_PRINT
  PRINT_CURRENT_BUF_POSITION( "", Data, EncData, BitOfEnc, BitsOfIndex, DataToSend );
#endif
  return true;
}



int CheckDiff ()	
{			
  return MAX_LEN_BUF_BITS - BitsOfIndex;
}


/*
 * FIXME : Need to Re-check
 */

bool WriteInToFile(int FileDes, int Bytes )
{
  uint8_t *uPtr8 ;
  int i;
  // console_print( "%s Called Bit %d\n", __func__, BitsOfIndex );

  uPtr8 = ( uint8_t *) &DataToSend + Bytes-1;

  for( i=0 ;i < Bytes; i++)	  // FIXME : Change it to -> based on BitIndex writing into file
  {
    if( write( FileDes, uPtr8, 1) < 0 )
    {
      console_print("DATA WRITTEN FAILURE : %s\n", strerror(errno));
      return false;
    }
    else
    {
#if 0
      console_print("DATA WRITTEN INTO FILE : %x\n", *uPtr8);
#endif
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
      console_print("Read Error: %s", strerror(errno));
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
  console_print("Done\n");
}

