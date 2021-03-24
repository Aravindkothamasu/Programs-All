#include "Huffman_Header.h"

void main (int argc, char **argv)
{  
  char *Ext;
  int   FileDes = -1;

  CmdLineCheck(argc);
  CheckFile( argv[0]);
  InFileDes = OpenInFile( argv[0] );
  Ext = GetOutFileExtent ( InFileDes, argv[0] );
  OutFileName = CreateOutFileName( Ext, argv[0]);

  FileDes = FileOpening( OutFileName, WRITE_MODE_FILE);



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
char * GetOutFileExtent( int InFileDes, char *InFileName)
{

  return ;
}

int OpenInFile( char *FileName)
{
  int FileDes = -1;

  FileDes = open( FileName, READ_MODE_FILE );
  if( FileDes < 0)
    console_print("Unable to open the input File : %s Reason : %s\n",
	FileName, strerror(errno));
  else
    console_print("File Open SUCCESS\n");

  return FileDes;
}

char *GetOutFileExtent (char *BinFileName)
{



}


void CheckFile( char *FileName)
{
  char temp[5] = ".bin";
  int len = 0;

  len = strlen( FileName) -1;

  for( i=0;i<4;i++)
    if( temp[i] != FileName[len-3+i] )
    {
      console_print("Error in FileName extention : %s\n", FileName);
      exit(0);
    }
}

void CmdLineCheck(int argc)
{
  if( argc != 2 )
  {   
    console_print("ERROR CMLD LINE USAGE : ./Decode   [Input File.bin]\n");
    exit(0);
  }
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
