#include "luhn.h"

sai_Luhn_t App = {0};

int main( int argc, char **argv) 
{

  console_print("==========   LUHN Application Started   =============\n");

  CheckCmdLineArg( argc, argv );
  ValidateData( &App, argv );
  AnalyzeData( argc, argv );

  PrintData( &App );
  if( LuhnAlgorithm( &App ) )
  {
    console_print("[%s] is Number is valid\n", argv[1] );
  }
  else
  {
    console_print("[%s] is not a Luhn Valid number\n", argv[1]);
  }

  console_print("=========  LUHN Applicatiom Done  ============\n");

  return 0;
}

bool LuhnAlgorithm( sai_Luhn_t *AppPtr )
{
  int8_t  Indx, temp = 0;
  int RtnVal;

  for( Indx = AppPtr->Len -2 ; Indx >= 0 ; Indx -= 2 )
  {
    console_print("Data : %d\n", AppPtr->Data[Indx] );
    AppPtr->Data[Indx] *= 2;
    console_print("After Multiply Data : %d\n", AppPtr->Data[Indx] );
  }

  for( Indx = AppPtr->Len - 2; Indx >= 0 ; Indx -= 2 )
  {
    temp = AppPtr->Data[Indx] / 10 ;
    AppPtr->Data[Indx] %= 10;
    AppPtr->Data[Indx] += temp;
    console_print("Data after recieved : %d\n", AppPtr->Data[Indx] );
  }

  RtnVal = SumOfDigits( AppPtr );

  if( 0 == (RtnVal % 10 ) )
    return true;
  else
    return false;
}

int SumOfDigits( sai_Luhn_t *AppPtr )
{
  int RtnVal = 0, i;
  
  for( i = 0 ;i < AppPtr->Len ; i++ )
  {
    RtnVal += AppPtr->Data[i]; 
  }
  console_print("Sum Of Digits : %d\n", RtnVal );
  return RtnVal;
}


void PrintData( sai_Luhn_t *AppPtr )
{
  int i;

  console_print("====  RAW Data ======\n");
  for( i = 0;i < AppPtr->Len; i++ )
    printf( "%d   ", AppPtr->Data[i] );

  printf("\n\n");
}

void ValidateData( sai_Luhn_t *AppPtr, char **argv )
{
  AppPtr->Len = strlen( argv[1] );
  if( AppPtr->Len >= MAX_LEN_NUMBER )
  {
    console_print( "Input Data more can't Process\n");
    exit( 0 );
  }
  else if( AppPtr->Len <= 1 )
  {
    console_print( "Input Data is too short Len %d || Data: %s\n", AppPtr->Len, argv[1] );
    exit( 0 );
  }
  else
    console_print("Data Len : %d\n", AppPtr->Len );
}

void AnalyzeData( int argc, char ** argv)
{
  int i=0;
  console_print("Analyze Data Function Called\n");


  for( i = 0; i < App.Len ; i++ )
  {
    if( argv[1][i] >= '0' && argv[1][i] <= '9' )
    {
      App.Data[i] = argv[1][i] - '0';
    }
    else
    {
      console_print( "Wrong Input Data : %s\n", argv[1] );
      exit( 0 );
    }
  }
}



void CheckCmdLineArg( int argc, char **argv )
{
  if( argc != 2 )
  {
    console_print( "Command Line usage Error : [./a.out NUMERIC STRING]\n");
    exit( 0 );
  }
}



void FramingData( int Line, const char *Func, const char *File, const char *format, ...)
{								    
  char Buffer[500]={0};
  va_list args;
  va_start( args, format);					    
  sprintf( Buffer, "#%s#  %s() [%3d] : ", File, Func, Line);	    
  vsprintf( &Buffer[strlen(Buffer)], format, args);		    
  va_end(args);	
  printf("%s", Buffer);
}
