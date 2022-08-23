#include "include/Huffman_Header.h"


char PrintBuffer[500]={0};

void CmdLineCheck(int argc, int MaxCount)
{
  if( argc != MaxCount)
  {   
    console_print("ERROR CMLD LINE USAGE : ./Encode   [Input File]\n");
    exit(0);
  }

  return;
}


int FileOpening (char *Filename, short int Flags)
{
  int FileDes;
  FileDes = open( Filename, Flags,0664);

  if ( -1 == FileDes )
  {
    console_print("ERROR IN FILE OPENING : %s ,REASON : %s\n",Filename,strerror(errno));
    exit(0);
  }

  return FileDes;
}



void FramingData( int Line, const char *Func, const char *File, const char *format, ...)
{								    
  va_list args;
  va_start( args, format);					    
  sprintf( PrintBuffer, "#%8s#  %18s() [%3d] : ", File, Func, Line);	    
  vsprintf( &PrintBuffer[strlen( PrintBuffer)], format, args);		    
  va_end(args);	
  printf("%s", PrintBuffer);
}


bool WriteDataIntoFile( int OutFileDes, uint8_t *DataPtr, int DataLen )
{
  if( -1 == write( OutFileDes, DataPtr, DataLen ) )
  {
    console_print(" Write SYSTEM call fails : %s", strerror(errno));
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
    // console_print( "BYTEINDEX %d || BITINDEX %d\n", ByteIndex, BitIndex );

    if( true == GetBitValInArray( a, Index-- ))
      Buf[ StrLen++ ] = '1';
    else
      Buf[ StrLen++ ] = '0';


    if( 0 == ByteIndex && BitIndex == 0 )
    {
      // console_print( "%s\n", Buf );
      break;
    }

    if( BitIndex == 4 || BitIndex == 0 )
      Buf[ StrLen++ ] = '|';

    if( BitIndex == 0 )
      Buf[ StrLen++ ] = '|';

    if( BitIndex == 0 )
    {
      // console_print( "\n" );
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

  // console_print( "BYTE INDX %d BIT %d\n", ByteIndex, BitIndex );

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


