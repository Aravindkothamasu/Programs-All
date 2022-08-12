#include "include/Huffman_Header.h"



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



char PrintBuffer[500]={0};

void FramingData( int Line, const char *Func, const char *File, const char *format, ...)
{								    
  va_list args;
  va_start( args, format);					    
  sprintf( PrintBuffer, "#%8s#  %18s() [%3d] : ", File, Func, Line);	    
  vsprintf( &PrintBuffer[strlen( PrintBuffer)], format, args);		    
  va_end(args);	
  printf("%s", PrintBuffer);
}

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



float Percentage_FillUp( int SlaveId, int WritePtr, int ReadPtr )
{
  /*
  int Diff=0;
  float percent;

  if ( WritePtr >= ReadPtr )
  {
    Diff = WritePtr - ReadPtr;
  }
  else
  {
    Diff = MAX_LEN_BUF_BITS - ( ReadPtr - WritePtr );
  }

  percent = ((Diff)/( MAX_LEN_BUF_BITS * 1.0)) * 100.0f;
  return percent;
  */

  // TODO : Need to add
  return 0;
}

