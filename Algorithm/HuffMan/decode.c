#include "include/Huffman_Decode_Header.h"

#define	    SAMPLE_TEST		  0

int EncDataByts = 0;
char temp_print_buf[256]={0};


#if SAMPLE_TEST
int	 Counter=0;
uint64_t SampleBinData =  0;
int	 SampleWrIndex =  1;
int	 SampleRdIndex =  0;

#endif



uint8_t  BinDataBuf[DECODE_BUF_BYTES]	= {0};
int	 BinDataWrIndex			=  0;
int	 BinDataRdIndex			=  0;


uint8_t  LastBitPosBuf[5]		= {0};
int	 LastBitPosIndex		=  0;



uint8_t	 DSCountBuf[5]			= {0};
int	 DSCountIndex			=  0;


uint8_t  FileSizeBuf[12]	        = {0};
int	 FileSizeBufIndex		=  0;



float	PercentageFileRead		=  0;



int	LogFileDes			=  0;
int     DebugSt				=  0;


/*
 *  main() -> Main Function Starts here.
 */

int main (int argc, char **argv)
{  
  int FileIndex;
  Huff_Decode_app_t App={0};

  CmdLineCheck( argc, 2 );

  App.RdRtnBytes = 4;

  for( FileIndex = 1; FileIndex < argc; FileIndex++ )
    DecodeHuffMan( &App, argv[FileIndex] );

  printf( "ARGC  %d\n", argc );
  ProgramExit( true );
  return 0;
}



void DecodeHuffMan(Huff_Decode_app_t *AppPtr, char * InputFileName )
{
  uint32_t i = 0;
  int Rtn;


  while( true )
  {
    if( AppPtr->MainSt >= DEC_ENCRYPT_METADATA )
    {
      ReadDataIpSrcFile( AppPtr ); 

      if( -1 == AppPtr->RdRtnBytes )
      {
	console_print( LOG_ERROR, "Input File Read Error : %s\n", strerror(errno));
	ProgramExit( false );
      }
      else if( 0 == AppPtr->RdRtnBytes )
      { // FIXME : Change

	ClosingCeremony( AppPtr );
	return;
      }
    }

    for( i = 0 ; i < AppPtr->RdRtnBytes ; i++ )
    {
      switch( AppPtr->MainSt )
      {
	case DEC_CHCK_IN_FILE :
	  {
	    CheckIpFile( InputFileName );

	    console_print( LOG_GEN, "========  Check Input File Done  =========\n");
	    AppPtr->MainSt = DEC_IN_FILE;
	  }
	  break;

	case DEC_IN_FILE :
	  {
	    AppPtr->InFileDes = FileOpening( InputFileName, READ_MODE_FILE);

	    AppPtr->MainSt = DEC_CREATE_OUT_FILENAME;
	  }
	  break;

	case DEC_CREATE_OUT_FILENAME :
	  {
	    CreateOutFileName( AppPtr->OutFileName, InputFileName );
	    AppPtr->MainSt = DEC_OPEN_OUTFILE;
	  }
	  break;

	case DEC_OPEN_OUTFILE :
	  {
	    // FIXME : Need to check whether it is right or not.
	    LogFileDes = FileOpening( CreateLogFilename( DECODE_LOG_DIR_PATH, InputFileName ), WRITE_MODE_FILE );
	    AppPtr->OutFileDes = FileOpening( AppPtr->OutFileName, WRITE_MODE_FILE);

	    console_print( LOG_GEN, "I/p FileName : %s\n", InputFileName );
	    console_print( LOG_GEN, "O/p FileName : %s\n", AppPtr->OutFileName);

	    AppPtr->MainSt = DEC_ENCRYPT_METADATA;
	  }
	  break;

	case DEC_ENCRYPT_METADATA :
	  {
	    Rtn = ReadMetaData( AppPtr, AppPtr->IpData[i] );

	    if( -1 == Rtn )
	    {
	      i--;
	      if( AppPtr->MetadataSt == METADATA_LAST_BIT ) 
		AppPtr->MainSt = DEC_HEADER;
	    }
	    else if( 1 == Rtn )
	    {
	      AppPtr->MainSt = DEC_HEADER;
	    }
	    else if( 0 == Rtn )
	    {
	      // read metadata is incomplete
	    }

	  }
	  break;

	case DEC_HEADER :
	  {
#if ENCRYPT_HEADER
	    if( true == CheckEncode( true, AppPtr->IpData + i ) )
	    {
	      console_print( LOG_MAPPING, "============  Decoding HEADER SUCCESS  ===========\n\n");
	      i += 3;
	      AppPtr->MainSt = DEC_MAP_DATA;
	    }
	    else
	    {
	      console_print( LOG_ERROR, "**** DEC Header Else Executed \n" );
	      return;
	    }
#else
	    i--;    // In Case Header is not enabled, skip the state and decrement index value
	    AppPtr->MainSt = DEC_MAP_DATA;
#endif
	  }
	  break;

	case DEC_MAP_DATA :
	  {
	    // FIXME : Handle Last Byte of the array
	    if( true == MapData( AppPtr, AppPtr->IpData[i], sizeof( uint8_t) * 8 ) )
	    {
	      // console_print( LOG_MAPPING, "============  Mapping Data SUCCESS  ===========\n");
	      // AppPtr->MainSt = DEC_FOOTER;
	    }
	    else
	    {
	      console_print( LOG_ERROR, "Something nasty things has happened, control should not come here\n" );
	      return;
	    }
	  }
	  break;

	case DEC_FOOTER:
	  {
	    if( true == CheckEncode( false, AppPtr->IpData + i ) )
	    {
	      console_print( LOG_MAPPING, "============  Decoding FOOTER SUCCESS  ===========\n");
	      return;
	    }
	    else
	      return;
	  }
	  break;

	default :
	  {
	    console_print( LOG_ERROR,"Unknown State : %d\n", AppPtr->MainSt );
	    exit ( 0 );
	  }
	  break;
      }
    }
  }
}




void PrcsIpData( Huff_Decode_app_t *AppPtr, uint8_t Data )
{
  // console_print( LOG_GEN, "%s HDDR Called || ST %d || DATA : %2X \n", __func__, AppPtr->DataFlowSt, Data );

  switch( AppPtr->DataFlowSt )
  {
    case DS_HDDR_STR_1 :
      {
	if( DATA_ST_BYTE_0 != Data )
	{
	  if( ENCODE_HEADER_1 == Data ) 
	    return;
	  else
	  {
	    console_print( LOG_ERROR,"Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
		DATA_ST_BYTE_0, Data );
	    ProgramExit( false );
	  }
	}
	else
	  AppPtr->DataFlowSt = DS_HDDR_STR_2;
      }
      break;

    case DS_HDDR_STR_2 :
      {
	if( DATA_ST_BYTE_1 != Data )
	{
	  console_print( LOG_ERROR,"Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_1, Data );
	  ProgramExit( false );
	}
	else
	  AppPtr->DataFlowSt = DS_DATA_TYPE;
      }
      break;

    case DS_DATA_TYPE :
      {
	AppPtr->DataPtr [AppPtr->Indx]->Type = Data;
	AppPtr->DataFlowSt = DS_DATA_BIT_ENC;
      }
      break;

    case DS_DATA_BIT_ENC:
      {
	AppPtr->DataPtr[AppPtr->Indx]->BitOfEnc = Data;
	EncDataByts = ( AppPtr->DataPtr[AppPtr->Indx]->BitOfEnc / 8 ) + 1;

	AppPtr->DataFlowSt = DS_DATA_ENC_DATA;
      }
      break;

    case DS_DATA_ENC_DATA:
      {
	AppPtr->DataPtr[AppPtr->Indx]->EncData = 
	  AppPtr->DataPtr[AppPtr->Indx]->EncData << 8 | Data;

	--EncDataByts;
	if( 0 == EncDataByts )
	  AppPtr->DataFlowSt = DS_DATA_FOOT_1;
      }
      break;

    case DS_DATA_FOOT_1 :
      {
	if( DATA_ST_BYTE_5 != Data )
	{
	  console_print( LOG_ERROR,"Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_5, Data );
	  ProgramExit( false );
	}
	else
	  AppPtr->DataFlowSt = DS_DATA_FOOT_2;
      }
      break;

    case DS_DATA_FOOT_2 :
      {
	if( DATA_ST_BYTE_6 != Data )
	{
	  console_print( LOG_ERROR,"Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_6, Data );
	  ProgramExit( false );
	}
	else
	{
	  AppPtr->Indx++;
	  AppPtr->DataFlowSt = DS_HDDR_STR_1;
	  // console_print( LOG_MAPPING, "INDEX : %d\n", AppPtr->Indx );
	}
      }
      break;


    default : 
      console_print( LOG_ERROR, " Error in Getting State");
      ProgramExit( false );
  }

  return;
}




/*
   Return
   -1 -> Current State is disabled
   0 -> Metadata read incomplete.
   1 -> Metadata read complete.
 */


int ReadMetaData( Huff_Decode_app_t *AppPtr, uint8_t Data )
{
  // console_print( LOG_MAPPING, "%s   Data : %2X : ST : %d\n", __func__, Data, AppPtr->MetadataSt );

  switch( AppPtr->MetadataSt )
  {

    case METADATA_FILE_SIZE:
      {

#if  ENCRYPT_FILE_SIZE
	if( true == GetSourceFileSize( Data, &AppPtr->SrcFileSizeInBytes ))
	{
	  console_print( LOG_MAPPING, "-------- ENCRYPT File Size Writing DECIMAL : %ld  || HEX : %lX Done\n\n", 
	      AppPtr->SrcFileSizeInBytes, AppPtr->SrcFileSizeInBytes );
	  AppPtr->MetadataSt = METADATA_COUNT_DS;

	}
#else
	console_print( LOG_ERROR, "-------- ENCRYPT File Size DISABLED\n\n");
	AppPtr->MetadataSt = METADATA_COUNT_DS;
	return -1;
#endif

      }
      break;

    case METADATA_COUNT_DS:
      {

#if ENCRYPT_COUNT_DS

	if( true == GetCountDS( Data, &AppPtr->CountIndex ))
	{
	  if( AppPtr->CountIndex < 0 )
	  {
	    console_print( LOG_ERROR,"Error in Reading Binary Data\n");
	    // TODO : ProgramExit()
	  }
	  console_print( LOG_MAPPING,"============   CountIndex : Hex : %2X || Dec %d   ===========\n",
	      AppPtr->CountIndex, AppPtr->CountIndex);

	  AppPtr->MetadataSt = METADATA_READ_DS;

	  MemoryAllocation( &AppPtr->DataPtr, AppPtr->CountIndex );
	}

#else
	console_print( LOG_MAPPING, "-------- ENCRYPT Count DS is DISABLED\n\n");
	AppPtr->MetadataSt = METADATA_READ_DS;
	return -1;
#endif
      }
      break;


    case METADATA_READ_DS:
      {
	PrcsIpData ( AppPtr, Data );

	if( AppPtr->Indx == AppPtr->CountIndex )
	{
	  console_print( LOG_MAPPING,"============  Reading the Frame Format Completed ===========\n");
	  PrintDSdata( AppPtr );
	  AppPtr->MetadataSt = METADATA_LAST_BIT;
	}
      }
      break;


    case METADATA_LAST_BIT:
      {

#if ENCRYPT_LAST_BIT_INDEX
	{
	  LastBitPosBuf[LastBitPosIndex++] = Data;
	  // console_print( LOG_MAPPING, "---LAST BIT POS DATA FEED : %d -- %2X\n", LastBitPosIndex, Data );
	  if( LastBitPosIndex < 5 )
	    break;

	  ReadLastBitPostion( &AppPtr->LastBitPos );
	  console_print( LOG_MAPPING, "LastBit Position --> %ld\n", AppPtr->LastBitPos );

	  return  1;
	}
#else
	console_print( LOG_MAPPING , "-------- ENCRYPT LAST BIT INDEX DISABLED\n\n");
	return -1;
#endif
      }
      break;
  }

  return 0;
}


void ClosingCeremony(  Huff_Decode_app_t *AppPtr )
{
  Decode_ParseData( AppPtr, BinDataBuf, &BinDataRdIndex, &BinDataWrIndex );
  console_print( LOG_GEN, "READ DONE\n" );

  AppPtr->OutFileWrittenBytes += AppPtr->OutFileBufIndex;
  WriteDataIntoFile( AppPtr->OutFileDes, AppPtr->OutFileBuf, AppPtr->OutFileBufIndex );
  close( AppPtr->OutFileDes );
  close( AppPtr->InFileDes );

  PrintFillUpData( AppPtr->SrcFileSizeInBytes, AppPtr->OutFileWrittenBytes, 100.0f ); 

  console_print( LOG_MAPPING, "\n" );
  console_print( LOG_MAPPING, "==============================================================\n" );
  console_print( LOG_MAPPING, "======    BYTES ORIGINAL FILE : %12d Bytes	=======\n", AppPtr->SrcFileSizeInBytes );
  console_print( LOG_MAPPING, "======    BYTES WRIITEN  FILE : %12d Bytes	=======\n", AppPtr->OutFileWrittenBytes );
  console_print( LOG_MAPPING, "==============================================================\n" );
  console_print( LOG_MAPPING, "\n" );

  if( LogFileDes > 0 )
    close( LogFileDes );
  LogFileDes = -1;

  FreeupMemory( AppPtr );
}

void AddDataWriteBuf( Huff_Decode_app_t *AppPtr, uint8_t Data )
{
  AppPtr->OutFileBuf[ AppPtr->OutFileBufIndex++ ] = Data;

  if( AppPtr->OutFileBufIndex >= DECODE_OUT_BUF_MAX_LEN )
  {
    WriteDataIntoFile( AppPtr->OutFileDes, AppPtr->OutFileBuf, AppPtr->OutFileBufIndex );

    AppPtr->OutFileWrittenBytes += AppPtr->OutFileBufIndex;
    memset( &AppPtr->OutFileBuf, 0, DECODE_OUT_BUF_MAX_LEN );
    AppPtr->OutFileBufIndex = 0;
  }
}


void ReadLastBitPostion( uint8_t *LastBitPosPtr )
{
  if (
      ( ASCII_DLE == LastBitPosBuf[0] ) &&
      ( ASCII_STX == LastBitPosBuf[1] ) &&
      ( ASCII_DLE == LastBitPosBuf[3] ) &&
      ( ASCII_STX == LastBitPosBuf[4] ) )
  {
    *LastBitPosPtr = LastBitPosBuf[2];
  }
  else
    console_print( LOG_ERROR, "---- Error in Reading LastBitPosBuf \n" );

}



void PrintDSdata(  Huff_Decode_app_t  * AppPtr )
{
  int i;
  char Temp[150] = {0};

  for( i=0; i < AppPtr->CountIndex ; i ++ )
  {
    GetBinary( AppPtr->DataPtr[i]->EncData, sizeof( uint64_t ), Temp );
    console_print( LOG_MAPPING,"INDX[%3d] Data : %2X | BitEnc %2d | EncData : %6X | Bin : %s\n",
	i+1, 
	AppPtr->DataPtr[i]->Type, 
	AppPtr->DataPtr[i]->BitOfEnc, 
	AppPtr->DataPtr[i]->EncData, Temp );
  }
}

int ReadDataIpSrcFile( Huff_Decode_app_t *AppPtr )
{
  memset( AppPtr->IpData, 0, sizeof( AppPtr->IpData ) );

  AppPtr->RdRtnBytes = read( AppPtr->InFileDes, AppPtr->IpData, DECODE_IN_BUF_MAX_LEN );

  if( -1 == AppPtr->RdRtnBytes )
  {
    console_print( LOG_ERROR,"Error in Reading from input File : %s\n", strerror( errno ));
  }
  else if( 0 == AppPtr->RdRtnBytes )
  {
    console_print( LOG_GEN,"Reading from input File DONE \n" );
  }
  console_print( LOG_PRIO, "%s Called Bytes Read : %d\n", __func__ , AppPtr->RdRtnBytes );
  return AppPtr->RdRtnBytes;
}




bool isLetterMatch( uint64_t EncData1, int BitOfEnc1, uint8_t *EncData2, int BitOfEnc2 )
{
  bool Operator1 = false;
  bool Operator2 = false;
  int  i, lBinDataRdIndx = 0;

  // console_print( LOG_MAPPING, "DataPtr Type : %X || Bit %2d || EncData %X\n", 
  // DataPtr->Type, DataPtr->BitOfEnc, DataPtr->EncData );

  lBinDataRdIndx = BitOfEnc2;

  for( i = BitOfEnc1-1; i >= 0; i-- )
  {
    Operator1 = GetBitVal( EncData1, i );
    Operator2 = GetBitValInArray( EncData2, lBinDataRdIndx );
    INCCIRCULARINDEX( lBinDataRdIndx, DECODE_BUF_BITS_LEN );

    // console_print( LOG_GEN, "INDEX : %d || Ope1 : %d || Ope2 : %d\n", i, Operator1, Operator2 );
    if( Operator1 != Operator2 )
    {
      // console_print( LOG_GEN, "==== Un-Match ====\n" );
      return false;
    }
  }

  return true;
}



void Decode_ParseData( Huff_Decode_app_t *AppPtr, uint8_t *BinDataBufPtr, int *BinDataRdIndexPtr, int *BinDataWrIndexPtr )
{
  int i, ElementIndex = 0;
  Huff_Decode_DataStru_t *DataPtr = NULL;

  do{
    DataPtr = AppPtr->DataPtr[ElementIndex];

    if( Percentage_FillUp( DECODE_BUF_BITS_LEN, *BinDataWrIndexPtr, *BinDataRdIndexPtr ) <= DataPtr->BitOfEnc ) 
      // FIXME : Re-check the condition
    {
      console_print( LOG_PRIO, "ElementIndex : %d || Bin Data : %lX || WrIndex : %d || RdIndex : %d || Diff %d\n", 
	  ElementIndex, *BinDataBufPtr, *BinDataWrIndexPtr, *BinDataRdIndexPtr, 
	  Percentage_FillUp( DECODE_BUF_BITS_LEN, *BinDataWrIndexPtr, *BinDataRdIndexPtr) );

      console_print( LOG_PRIO, "WrIndex Buf is empty returning..\n" );

      return;
    }
    // console_print( LOG_PRIO, "=========	  ElementIndex : %2d || WrIndex : %2d || RdIndex : %2d || BitOfEnc %d\n", 
    // ElementIndex, *BinDataWrIndexPtr, *BinDataRdIndexPtr, DataPtr->BitOfEnc );

    if( true == isLetterMatch( DataPtr->EncData, DataPtr->BitOfEnc, BinDataBufPtr, *BinDataRdIndexPtr )) 
    {

      console_print( LOG_PRIO, "BEF EleIndx %2d | Data %lX | WrIndx %2d | RdIndx %2d | Diff %d - %s\n", 
	  ElementIndex, DATA_BUF( BinDataBufPtr, DECODE_BUF_BYTES), *BinDataWrIndexPtr, *BinDataRdIndexPtr, 
	  Percentage_FillUp( DECODE_BUF_BITS_LEN,  *BinDataWrIndexPtr, *BinDataRdIndexPtr),
	  GetBinaryInArray( BinDataBufPtr, DECODE_BUF_BYTES, temp_print_buf) );

      console_print( LOG_PRIO, "DATA READ Indx %2d Data %X EncData %2X BitOfEnc %2d ----  WRINDX %2d RDINDX %2d\n", 
	  ElementIndex,
	  DataPtr->Type,
	  DataPtr->EncData,
	  DataPtr->BitOfEnc,
	  *BinDataWrIndexPtr,
	  *BinDataRdIndexPtr );

      ElementIndex = 0;

      AddDataWriteBuf( AppPtr, DataPtr->Type );

      for( i = 0; i < DataPtr->BitOfEnc; i++)
      {
	INCCIRCULARINDEX( *BinDataRdIndexPtr, DECODE_BUF_BITS_LEN );
      }

      console_print( LOG_PRIO, "AFT EleIndx %2d | Data %lX | WrIndx %2d | RdIndx %2d | Diff %d - %s\n", 
	  ElementIndex, DATA_BUF( BinDataBufPtr, DECODE_BUF_BYTES ), *BinDataWrIndexPtr, *BinDataRdIndexPtr, 
	  Percentage_FillUp( DECODE_BUF_BITS_LEN, *BinDataWrIndexPtr, *BinDataRdIndexPtr),
	  GetBinaryInArray( BinDataBufPtr, 8, temp_print_buf));
      console_print( LOG_PRIO, "\n\n" );

    }
    else
    {
      INCCIRCULARINDEX( ElementIndex, AppPtr->CountIndex ); 
      if( 0 == ElementIndex )
      {
	ProgramExit(false);
      }
    }

  }while( true );
}


void PrintPercentageFileRead( Huff_Decode_app_t *AppPtr )
{
  float FilledUp = 0;

  FilledUp = (float) ( ( AppPtr->OutFileWrittenBytes * 100 ) / AppPtr->SrcFileSizeInBytes );

  if( FilledUp != PercentageFileRead )
  {
    PercentageFileRead = FilledUp;

    PrintFillUpData( AppPtr->SrcFileSizeInBytes, AppPtr->OutFileWrittenBytes, PercentageFileRead );
  }
}


bool MapData( Huff_Decode_app_t *AppPtr, uint8_t EncData, int BitOfEnc)
{
  int i;

  console_print( LOG_PRIO, "BMAP ENC %02X BitOfEnc %d || WRINDX %2d RDINDX %2d DIFF %2d DATA %llX \n", 
      EncData, BitOfEnc, BinDataWrIndex, BinDataRdIndex, 
      Percentage_FillUp( DECODE_BUF_BITS_LEN, BinDataWrIndex, BinDataRdIndex), DATA_BUF( BinDataBuf, DECODE_BUF_BYTES ) );


  if( Percentage_FillUp( DECODE_BUF_BITS_LEN, BinDataWrIndex, BinDataRdIndex) > DECODE_BUF_BITS_LEN - 10 )
  {
    // console_print( LOG_PRIO, "PERCENTAGE FILLEDUP EncData : %02X BitOfEnc %d\n", EncData, BitOfEnc );

#if SAMPLE_TEST
    AppendData(AppPtr);
    Counter++;
    Decode_ParseData( AppPtr, SampleBinData, &SampleRdIndex, &SampleWrIndex );
#else
    Decode_ParseData( AppPtr, BinDataBuf, &BinDataRdIndex, &BinDataWrIndex );
#endif

    PrintPercentageFileRead( AppPtr );
  }

  for( i = BitOfEnc -1 ; i >= 0; i-- )
  {
    BitFeed( BinDataBuf, BinDataWrIndex, GetBitVal( EncData, i ) );
    // console_print( LOG_GEN, "BIT INDX : %2d | VAL : %d\n", BinDataWrIndex, GetBitVal( EncData, i ));
    INCCIRCULARINDEX( BinDataWrIndex, DECODE_BUF_BITS_LEN );
  }
  console_print( LOG_PRIO, "%s\n", GetBinaryInArray( BinDataBuf, DECODE_BUF_BYTES, temp_print_buf) );
  // sleep(1);
  return true;
}



bool CheckEncode( bool isHeader, uint8_t *DataRead )
{
  if ( isHeader )
  {
    if( ( ENCODE_HEADER_1 == DataRead[0] ) && ( ENCODE_HEADER_2 == DataRead[1] ) &&
	( ENCODE_HEADER_3 == DataRead[2] ) && ( ENCODE_HEADER_4 == DataRead[3] ) )
    {
      console_print( LOG_MAPPING,"Encoding HEADER PASSED\n");
      return true;
    }
  }
  else
  {
    if( ( ENCODE_FOODER_1 == DataRead[0] ) && ( ENCODE_FOODER_2 == DataRead[1] ) &&
	( ENCODE_FOODER_3 == DataRead[2] ) && ( ENCODE_FOODER_4 == DataRead[3] ) )
    {
      console_print( LOG_MAPPING,"Encoding FOOTER PASSED\n");
      return true;
    }
  }
  console_print( LOG_ERROR,"Error in Parsing Encoding [%s] %X %X %X %X\n", isHeader ? "HEADER" : "FOOTER", 
      DataRead[0], DataRead[1], DataRead[2], DataRead[3]);
  return false;
}



int GetCountDS( uint8_t Data, int *CountIndexPtr )
{
  // console_print( LOG_MAPPING,"Decode Get Count Data Structure Called INDX : %d, Data : %2X\n", DSCountIndex, Data );

  DSCountBuf[DSCountIndex++] = Data;

  if( DSCountIndex < 5 )
  {
    return false;
  }

  if (
      ( START_INDEX_BYTE_0 == DSCountBuf[0] ) &&
      ( START_INDEX_BYTE_1 == DSCountBuf[1] ) &&
      ( START_INDEX_BYTE_3 == DSCountBuf[3] ) &&
      ( START_INDEX_BYTE_4 == DSCountBuf[4] ) )
  {
    *CountIndexPtr = DSCountBuf[2];
    return true;
  }

#if 1
  int Index;
  for( Index = 0; Index < 5; Index++ )
    console_print( LOG_MAPPING, "---- GetCountDS[%2d] -- %2X\n", Index, DSCountBuf[Index] );
#endif

  return true;
}




bool GetSourceFileSize( uint8_t Data, uint64_t *FileSizePtr )
{
  int Index;

  FileSizeBuf[FileSizeBufIndex++] = Data;

  if( FileSizeBufIndex < 12 )
  {
    return false;
  }

  for( Index = 0; Index < 12; Index++ )
    console_print( LOG_MAPPING, "GET SOURCE DATA : %02X\n", FileSizeBuf[Index] );

  if( ( ASCII_STX == FileSizeBuf[0] ) && ( ASCII_EOT == FileSizeBuf[1] ) &&
      ( ASCII_STX == FileSizeBuf[10] ) && ( ASCII_EOT == FileSizeBuf[11] ) )
  {
    console_print( LOG_MAPPING,"Getting File Size ENCRYPT PASSED\n");
    for( Index = 2; Index < 10; Index++ )
      *FileSizePtr = *FileSizePtr << 8 | FileSizeBuf[Index];
  }
  console_print( LOG_MAPPING, "SOURCE FILE SIZE HEX %lX  || DEC : %ld\n", *FileSizePtr, *FileSizePtr );

  return true;
}



void CreateOutFileName ( char *OutFileName, char *InFileName)
{
  console_print( LOG_MAPPING,"Create Out FileName Func Called\n");

  int Len = strlen( InFileName );

  strncpy( OutFileName, InFileName, Len - 4);
  strcat( OutFileName, "_cpy" );             //TODO : Remove after testing

  console_print( LOG_MAPPING,"Out FileName : %s\n", OutFileName);


}  

void CheckIpFile( char *FileName)
{
  char temp[5] = ".bin";
  char TempFileName[150]={0};
  int len = 0,i;


  strcpy( TempFileName, FileName);
  len = strlen( FileName) -1;

  for( i=0;i<4;i++)
    if( temp[i] != FileName[len-3+i] )
    {
      console_print( LOG_MAPPING, "Input FileName externtion is not ended with .bin\n");
      ProgramExit(false);
    }
}


//////////////////////////////////////////     MEMORY ALLOCATION FUNCTIONS	///////////////////////////////////////////////////

void FreeupMemory( Huff_Decode_app_t *AppPtr )
{
  int i;

  for( i = 0; i < AppPtr->CountIndex ; i++ )
  {
    free( AppPtr->DataPtr[i] );
  }
  free( AppPtr->DataPtr );
}

void MemoryAllocation( Huff_Decode_DataStru_t ***DataPtr, int CountIndex )
{
  if( true == AllocateMainMem( DataPtr, CountIndex ) )
    if( true == AllocateSubMemory( DataPtr, CountIndex ) )
      console_print( LOG_MAPPING, "============  Allocating Memory Success  ===========\n");
}


bool AllocateSubMemory( Huff_Decode_DataStru_t ***DataPtr, int CountIndex )
{
  int i;

  for( i = 0; i < CountIndex ; i++ )
  {
    (*DataPtr)[i] =  calloc( 1, sizeof( Huff_Decode_DataStru_t ) );

    if( NULL == (*DataPtr)[i] )
    {
      console_print( LOG_ERROR,"Unable to Allocate Memory for Sub Arrays Reason : %s", strerror( errno ));
      return false;
    }
  }
  return true;
}


bool AllocateMainMem( Huff_Decode_DataStru_t ***DataPtr, int CountIndex )
{
  *DataPtr = calloc( sizeof( Huff_Decode_DataStru_t ), CountIndex);

  if( NULL != *DataPtr )
  {
    console_print( LOG_MAPPING, "Allocated Main Memory ---- %d\n", CountIndex );
    return true;
  }
  else
    console_print( LOG_ERROR, "malloc failure : %s", strerror(errno ));

  return false;
}


uint64_t DATA_BUF( uint8_t *a, int Bytes )
{
  int	   i;
  uint64_t Data = 0;

  for( Data = 0, i = Bytes-1; i >= 0; i-- )
  {
    Data = Data << 8 | a[i];
  }
  return Data;
}


//////////////////////////////////////////////////////////////////////////////////////////////////



#if SAMPLE_TEST
void AppendData(Huff_Decode_app_t *AppPtr )
{
  int i;

  console_print( LOG_GEN, "****** Append Data *******\n" );
  if( Counter == 0 )
    SampleBinData = 0xf2ae535690194e40;
  else if( Counter == 1 )
  {
    GetBinary( SampleBinData, 8, temp_print_buf );
    console_print( LOG_GEN, "BEF : %s\n", temp_print_buf );

    SampleBinData = SampleBinData << 61 | 0xc5185d5cc304e96b >> 3;


    GetBinary( SampleBinData, 8, temp_print_buf );
    console_print( LOG_GEN, "AFT : %s\n", temp_print_buf );
  }
  else if( Counter == 2 )
  {

    GetBinary( SampleBinData, 8, temp_print_buf );
    console_print( LOG_GEN, "CNT 2 BEF : %s\n", temp_print_buf );

    SampleBinData = 0x6670;
    SampleWrIndex = 11;
    SampleRdIndex = 0;

    GetBinary( SampleBinData, 8, temp_print_buf );
    console_print( LOG_GEN, "CNT 2 AFT : %s\n", temp_print_buf );
    return;
  }
  else
  {
    SampleBinData = 0;
    SampleWrIndex = 0;
    return;

  }

  /*
     else if( Counter == 1 )
     SampleBinData = 0xc5185d5cc304e96b;
   */


  SampleWrIndex = 64;
}
#endif
