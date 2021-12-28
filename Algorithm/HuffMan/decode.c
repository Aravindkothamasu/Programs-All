#include "Huffman_Header.h"


int EncDataByts = 0;

int main (int argc, char **argv)
{  
  Huff_Decode_app_t App={0};

  CmdLineCheck( argc, 2);

  App.RdRtnBytes = 4;

  DecodeHuffMan( &App, argc, argv );
  return 0;
}

void DecodeHuffMan(Huff_Decode_app_t *AppPtr, int argc, char **argv )
{
  uint32_t i = 0;


  while( true )
  {
    if( AppPtr->MainSt >= DEC_DS_COUNT )
      ReadData( AppPtr ); 

    for( i = 0 ; i < AppPtr->RdRtnBytes ; i++ )
    {
      switch( AppPtr->MainSt )
      {
	case DEC_CHCK_IN_FILE :
	  {
	    CheckIpFile( argv[1]);

	    console_print("========  Check Input File Done  =========\n");
	    AppPtr->MainSt = DEC_IN_FILE;
	  }
	  break;

	case DEC_IN_FILE :
	  {
	    AppPtr->InFileDes = FileOpening( argv[1], READ_MODE_FILE);

	    AppPtr->MainSt = DEC_CREATE_OUT_FILENAME;
	  }
	  break;

	case DEC_CREATE_OUT_FILENAME :
	  {
	    CreateOutFileName( AppPtr->OutFileName, argv[1]);
	    AppPtr->MainSt = DEC_OPEN_OUTFILE;
	  }
	  break;

	case DEC_OPEN_OUTFILE :
	  {
	    AppPtr->OutFileDes = FileOpening( AppPtr->OutFileName, WRITE_MODE_FILE);

	    console_print("I/p FileName : %s\n", argv[1] );
	    console_print("O/p FileName : %s\n", AppPtr->OutFileName);

	    AppPtr->MainSt = DEC_DS_COUNT;
	  }
	  break;

	case DEC_DS_COUNT :
	  {
	    AppPtr->CountIndex = GetCountDS( AppPtr );
	    if( AppPtr->CountIndex < 0 )
	    {
	      console_print("Error in Reading Binary Data\n");
	      return;
	    }
	    else
	    {
	      i += 4;
	      console_print("============   CountIndex : Hex : %2X || Dec %d   ===========\n",
		  AppPtr->CountIndex, AppPtr->CountIndex);
	      AppPtr->MainSt = DEC_ALLOCATE;
	    }
	  }
	  break;

	case DEC_ALLOCATE :
	  {
	    if( true == AllocateMainMem( AppPtr ) )
	      if( true == AllocateSubMemory( AppPtr ) )
	      {
		console_print("============  Allocating Memory Success  ===========\n");
		i--;
		AppPtr->MainSt = DEC_GET_DS; 
		break;
	      }

	    console_print("Unable to Allocate memory in Main Strcuture \n");
	    exit( 0 );
	  }
	  break;

	case DEC_GET_DS :
	  {
	    if( true != PrcsIpData ( AppPtr, AppPtr->IpData[i] ) )
	    {
	      console_print("============  Reading the Frame Format Completed ===========\n");
	      i--;
	      PrintDSdata( AppPtr );
	      AppPtr->MainSt = DEC_HEADER;
	    }
	  }
	  break;

	case DEC_HEADER :
	  {
	    if( true == CheckEncode( true, AppPtr->IpData + i ) )
	    {
	      console_print("============  Decoding HEADER SUCCESS  ===========\n");
	      i += 3;
	      AppPtr->MainSt = DEC_MAP_DATA;
	    }
	    else
	      return;
	  }
	  break;

	case DEC_MAP_DATA :
	  {
	    if( true == MapData( AppPtr, AppPtr->IpData[i] ) )
	    {
	      console_print("============  Mapping Data SUCCESS  ===========\n");
	      AppPtr->MainSt = DEC_FOOTER;
	    }
	  }
	  break;

	case DEC_FOOTER:
	  {
	    if( true == CheckEncode( false, AppPtr->IpData + i ) )
	    {
	      console_print("============  Decoding FOOTER SUCCESS  ===========\n");
	      return;
	    }
	    else
	      return;
	  }
	  break;

	default :
	  {
	    console_print("Unknown State : %d\n", AppPtr->MainSt );
	    exit ( 0 );
	  }
	  break;
      }
    }
  }
}

bool PrcsIpData( Huff_Decode_app_t *AppPtr, uint8_t Data )
{
  switch( AppPtr->DataFlowSt )
  {
    case DS_HDDR_STR_1 :
      {
	if( DATA_ST_BYTE_0 != Data )
	{
	  if( ENCODE_HEADER_1 == Data ) 
	    return false;
	  else
	  {
	    console_print("Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
		DATA_ST_BYTE_0, Data );
	    exit( 0);
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
	  console_print("Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_1, Data );
	  exit( 0);
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
	  console_print("Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_5, Data );
	  exit( 0);
	}
	else
	  AppPtr->DataFlowSt = DS_DATA_FOOT_2;
      }
      break;

    case DS_DATA_FOOT_2 :
      {
	if( DATA_ST_BYTE_6 != Data )
	{
	  console_print("Data Read Error at Data Structure Act %2X Rcvd : %2X\n",
	      DATA_ST_BYTE_6, Data );
	  exit( 0);
	}
	else
	{
	  AppPtr->Indx++;
	  AppPtr->DataFlowSt = DS_HDDR_STR_1;
	}
      }
      break;


    default : 
      console_print( " Error in Getting State");
      exit( 0 );
  }
  return true;
}




void PrintDSdata(  Huff_Decode_app_t  * AppPtr )
{
  int i;

  for( i=0; i < AppPtr->CountIndex ; i ++ )
  {
    console_print("INDX[%3d] TYPE : %2X | BitEnc %2X | EncData : %8X\n",
	i+1, AppPtr->DataPtr[i]->Type, AppPtr->DataPtr[i]->BitOfEnc, AppPtr->DataPtr[i]->EncData );
  }
}

void ReadData( Huff_Decode_app_t *AppPtr )
{
  memset( AppPtr->IpData, 0, sizeof( AppPtr->IpData ) );

  AppPtr->RdRtnBytes = read( AppPtr->InFileDes, AppPtr->IpData, MAX_DATA_CAN_READ );

  if( -1 == AppPtr->RdRtnBytes )
  {
    console_print("Error in Reading from input File : %s\n", strerror( errno ));
    exit(0);
  }
}


bool AllocateSubMemory( Huff_Decode_app_t *AppPtr )
{
  int i;
  for( i = 0; i < AppPtr->CountIndex ; i++ )
  {
    AppPtr->DataPtr[i] =  calloc( 1, sizeof( Huff_Decode_DataStru_t ) );

    if( NULL == AppPtr->DataPtr[i] )
    {
      console_print("Unable to Allocate Memory for Sub Arrays Reason : %s", strerror( errno ));
      return false;
    }
  }
  return true;
}


bool AllocateMainMem( Huff_Decode_app_t *AppPtr)
{
  AppPtr->DataPtr = calloc( sizeof( Huff_Decode_DataStru_t ), AppPtr->CountIndex);

  if( NULL != AppPtr->DataPtr )
    return true;
  else
    console_print( "malloc failure : %s", strerror(errno ));

  return false;
}


bool MapData( Huff_Decode_app_t *AppPtr, uint8_t EncData)
{
  uint8_t IndxTmp = 0;
  uint8_t BitTmp  = 0;
  uint8_t FormatData = 7;

  console_print("****** MAP DATA CALLED ******\n");
  return false;
}

void WriteData( Huff_Decode_app_t *AppPtr )
{
  if( -1 == write( AppPtr->OutFileDes, AppPtr->OpData, AppPtr->WritePtr ) )
  {
    console_print("-----> Write Data into FILE : %s Failure : %s\n", strerror(errno) );
    exit( 0 );
  }
  else
    console_print("Writing Data SUCCESS : %d", AppPtr->WritePtr );
}

bool GetBitVal( uint64_t Data, uint8_t BitIndx )
{



  return false;
}

bool CheckEncode( bool isHeader, uint8_t *DataRead )
{
  if ( isHeader )
  {
    if( ( ENCODE_HEADER_1 == DataRead[0] ) && ( ENCODE_HEADER_2 == DataRead[1] ) &&
	( ENCODE_HEADER_3 == DataRead[2] ) && ( ENCODE_HEADER_4 == DataRead[3] ) )
    {
      console_print("Encoding FOOTER PASSED\n");
      return true;
    }
  }
  else
  {
    if( ( ENCODE_FOODER_1 == DataRead[0] ) && ( ENCODE_FOODER_2 == DataRead[1] ) &&
	( ENCODE_FOODER_3 == DataRead[2] ) && ( ENCODE_FOODER_4 == DataRead[3] ) )
    {
      console_print("Encoding FOOTER PASSED\n");
      return true;
    }
  }
  console_print("Error in Parsing Encoding [%s] %X %X %X %X\n", isHeader ? "HEADER" : "FOOTER", 
      DataRead[0], DataRead[1], DataRead[2], DataRead[3]);
  return false;
}




uint8_t ReadDS( Huff_Decode_DataStru_t *Ptr, int FileDes)
{
  uint8_t Data[7]={0};

  if( -1 == read( FileDes, Data, sizeof(Data)) )
  {
    console_print("Unable to Read the file : %s\n", strerror(errno));
    return 2;
  }
  else
  {
    /*
       console_print("Data Read Ds : %X %x %x %x %x %x %x\n",
       Data[0],
       Data[1],
       Data[2],
       Data[3],
       Data[4],
       Data[5],
       Data[6]);
     */
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


int GetCountDS( Huff_Decode_app_t * AppPtr )
{
  console_print("Decode Get Count Data Structure Called\n");

  if( START_INDEX_BYTE_0 != AppPtr->IpData[0] )
    return -1;
  if( START_INDEX_BYTE_1 != AppPtr->IpData[1] )
    return -1; 
  if( START_INDEX_BYTE_3 != AppPtr->IpData[3] )
    return -1; 
  if( START_INDEX_BYTE_4 != AppPtr->IpData[4] )
    return -1; 

  return AppPtr->IpData[2];
}


void CreateOutFileName ( char *OutFileName, char *InFileName)
{
  console_print("Create Out FileName Func Called\n");

  int Len = strlen( InFileName );

  strncpy( OutFileName, InFileName, Len - 4);
  strcat( OutFileName, "_Tmp");             //TODO : Remove after testing

  console_print("Out FileName : %s\n", OutFileName);


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
      console_print("Input FileName externtion is not ended with .bin\n");
      exit(0);
    }
}

