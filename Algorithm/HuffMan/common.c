#include "include/Huffman_Header.h"


char	PrintBuffer	      [1*1024]		= {0};
char	PercentagePrintStr    [250]		= {0};
char	FileNameBuf	      [512]		= {0};

extern	int   LogFileDes;
extern	int   DebugSt;



void CmdLineCheck(int argc, int MaxCount)
{
  // if( argc != MaxCount)
  if( argc < 2 )
  {   
    console_print( LOG_ERROR, "ERROR CMLD LINE USAGE : ./Encode  [FILE_1] [FILE_2]  ..... \n");
    ProgramExit( false );
  }

  return;
}

////////////////////////////////////////////	    FILE OPERATIONS	  /////////////////////////////////////

int FileOpening (char *Filename, short int Flags)
{
  int FileDes = -1;
  FileDes = open( Filename, Flags,0664);

  if ( -1 == FileDes )
  {
    console_print( LOG_ERROR, "ERROR IN FILE OPENING : %s ,REASON : %s\n",Filename,strerror(errno));
    ProgramExit( false );
  }

  return FileDes;
}

char * CreateLogFilename( char *Basepath, char *SrcFilename )
{
  bzero( FileNameBuf, sizeof( FileNameBuf ));

  strcpy( FileNameBuf, Basepath );
  // strncpy( FileNameBuf+strlen(FileNameBuf), SrcFilename, strlen( SrcFilename )-4 );
  strcat( FileNameBuf, SrcFilename );
  strcat( FileNameBuf, "_log" );
  
  console_print( LOG_GEN, "LOG FILENAME : %s\n", FileNameBuf );

  return FileNameBuf;
}


void FramingData( int LogType, int Line, const char *Func, const char *File, const char *format, ...)
{								    
  va_list args;
  va_start( args, format);					    

  bzero( PrintBuffer, sizeof( PrintBuffer ));

  if( ( !DebugSt ) && ( LogType == LOG_PRIO ))
    return;

  switch( LogType )
  {
    case LOG_ERROR:
      {
	strcpy( PrintBuffer, "LOG_ERROR  " );
      }
      break;

    case LOG_MAPPING:
      {
	strcpy( PrintBuffer, "LOG_MAP    " );
      }
      break;

    case LOG_GEN:
      {
	strcpy( PrintBuffer, "LOG_GEN    " );
      }
      break;

    case LOG_PRIO:
      {
	strcpy( PrintBuffer, "LOG_PRIO   " );
      }
      break;

    case LOG_SCREEN:
      {
	strcpy( PrintBuffer, "LOG_SCREEN " );
      }
      break;

    default:
      {
	printf( "================== DEFAULT STATE : %d\n", LogType );
      }
      break;
  }


  sprintf( PrintBuffer+strlen( PrintBuffer ), "#%8s#  %18s() [%3d] : ", File, Func, Line);	    
  vsprintf( &PrintBuffer[strlen( PrintBuffer)], format, args);		    
  va_end(args);	


  WriteLogFile( LogFileDes, LogType, PrintBuffer, strlen( PrintBuffer ));


  if( DebugSt || LogType == LOG_MAPPING || LogType == LOG_SCREEN || LogType == LOG_ERROR || LogFileDes <= 0 )
    printf("%s", PrintBuffer);
}

void WriteLogFile( int FileDes, int LogType, char *Data, int DataLen )
{
  if( FileDes > 0 )
  {
    if( LOG_SCREEN == LogType )
      return;

    if( LogType == LOG_PRIO )
    {
      if( DebugSt < 2 )
	return;
    }

    write( FileDes, PrintBuffer, strlen( PrintBuffer )); 
  }
}



bool WriteDataIntoFile( int OutFileDes, uint8_t *DataPtr, int DataLen )
{
  if( -1 == write( OutFileDes, DataPtr, DataLen ) )
  {
    console_print( LOG_ERROR, " Write SYSTEM call fails : %s", strerror(errno));
    return false;
  }
  else 
    return true;
}


int Percentage_FillUp( int MaxLen, int WritePtr, int ReadPtr )
{
  int Diff=0;

  if ( WritePtr >= ReadPtr )
  {
    Diff = WritePtr - ReadPtr;
  }
  else
  {
    Diff = MaxLen- ( ReadPtr - WritePtr );
  }
  return Diff;
}



void PrintFillUpData( int SrcFileSizeInBytes, int ProcessedFileBytes, float Value )
{
  int i;

  if( DebugSt == 0 )
  {
    system( "clear" );
    printf( "\n\n\n\n\n\n\n" );
  }

  console_print( LOG_SCREEN, "\t\t\t\t-----------	  SRC FILE BYTE : %d	    PROCESSED FILE BYTES : %d	-----------\n", 
      SrcFileSizeInBytes, ProcessedFileBytes );

  bzero( PercentagePrintStr, sizeof( PercentagePrintStr ));
  for( i = 0; i < 100; i++ )
    if( i < Value )
      strcat( PercentagePrintStr, "##" );
    else 
      strcat( PercentagePrintStr, "  " );

  console_print( LOG_SCREEN, "\t%s  :  (%2.2f)%%\n", PercentagePrintStr, Value );
}


////////////////////////////////////////////	    CREATING BINARY TO ARRAY	  /////////////////////////////////////


char * GetBinary (uint64_t  a,int size_in_bytes, char *Buf)	
{
  int i=0,bit=63;
  bzero( Buf, 128 );

  for( ;bit+1 ; i++ )
  {

    Buf[i] = ( a>>bit&1 ) ? '1' : '0';
    bit -= 1;

    if( 0 == (bit+1) % 4 )
      Buf[++i] = '|';
  }
  return Buf;
}


char * GetBinaryInArray (uint8_t *a,int size_in_bytes, char *Buf)	
{
  int ByteIndex = size_in_bytes-1;
  int BitIndex  = 7;
  int StrLen = 0;
  int Index = ( size_in_bytes * 8 ) -1;

  bzero( Buf, ( size_in_bytes * 8 ) + ( size_in_bytes * 2 ) );

  for( ; ; )
  {
    // console_print( LOG_GEN, "BYTEINDEX %d || BITINDEX %d\n", ByteIndex, BitIndex );

    if( true == GetBitValInArray( a, Index-- ))
      Buf[ StrLen++ ] = '1';
    else
      Buf[ StrLen++ ] = '0';


    if( 0 == ByteIndex && BitIndex == 0 )
    {
      // console_print( LOG_GEN, "%s\n", Buf );
      break;
    }

    if( BitIndex == 4 || BitIndex == 0 )
      Buf[ StrLen++ ] = '|';

    if( BitIndex == 0 )
      Buf[ StrLen++ ] = '|';

    if( BitIndex == 0 )
    {
      // console_print( LOG_GEN, "\n" );
      DECCIRCULARINDEX( ByteIndex, size_in_bytes );
    }
    DECCIRCULARINDEX( BitIndex, 8 );
  }

  return Buf;
}


//////////////////////////////////////	      BIT MANIPULATION OPERATIONS     ///////////////////////



void BitSet( uint8_t *DataPtr, int ByteIndex, int BitIndex )
{
  DataPtr[ByteIndex] |= 1 << BitIndex;
}

void BitClear( uint8_t *DataPtr, int ByteIndex, int BitIndex )
{
  DataPtr[ByteIndex] &= ~( 1 << BitIndex );
}

void BitFeed( uint8_t *ArrayPtr, int Index, bool BitValue )
{
  int ByteIndex = 0;
  int BitIndex	= 0;

  ByteIndex = Index/8;
  BitIndex  = Index - ( ByteIndex * 8 );

  // console_print( LOG_GEN, "BYTE INDX %d BIT %d\n", ByteIndex, BitIndex );

  if( true == BitValue )
    BitSet( ArrayPtr, ByteIndex, BitIndex );
  else
    BitClear( ArrayPtr, ByteIndex, BitIndex );
}



bool GetBitValInArray( uint8_t *arr, int Index )
{ 
  int ByteIndex = Index / 8;
  int BitIndex  = Index - ( ByteIndex * 8 );

  return (( arr[ByteIndex] >> BitIndex ) & 1);
}


bool GetBitVal( uint64_t Data, uint8_t BitIndex )
{
  return ( (Data >> BitIndex ) & 1 );
}

uint8_t BitReversal( uint8_t Data )
{
  int	  tempIndex = 0;
  uint8_t temp = 0;

  for( tempIndex = 0; tempIndex < 8; tempIndex++ )
    if( GetBitVal( Data, tempIndex) )
    {
      temp |= ( 1 << ( 7 - tempIndex ));
      console_print( LOG_ERROR, "BIT SET : %d || TEMP : %02X\n", tempIndex, temp );
    }
  return temp;
}







void ProgramExit( bool ExitState )
{
  if( false == ExitState )
  {
    console_print( LOG_ERROR, "====== SOME THING HAS STRUCK NEED TO EXIT ======\n" );
  }
  else
  {
    console_print( LOG_GEN, "====== APPLICATION EXIT ======\n" );
  }
  exit(0);
}


double GetEpochTimeMs(  )
{
  struct timeval tv = {0};
  double Rtn = 0;

  gettimeofday( &tv, NULL);

  Rtn = tv.tv_usec / 1000;
  Rtn /= 1000;
  Rtn += tv.tv_sec;

  return Rtn;
}



