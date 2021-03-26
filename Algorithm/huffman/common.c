#include "Huffman_Header.h"



int CmdLineCheck(int argc, int MaxCount)
{
  if( argc != MaxCount)
  {   
    console_print("ERROR CMLD LINE USAGE : ./Encode   [Input File]\n");
    exit(0);
  }
}


int FileOpening (char *Filename, int Flags)
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
  char Buffer[500]={0};
  va_list args;
  va_start( args, format);					    
  sprintf( Buffer, "#%s#  %s() [%d] : ", File, Func, Line);	    
  vsprintf( &Buffer[strlen(Buffer)], format, args);		    
  va_end(args);	
  printf("%s", Buffer);
}
