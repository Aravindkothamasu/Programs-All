
#include"Huffman_Header.h"

as_data_t CountData[TOT_CHARS+1]={0};

void main(int argc, char **argv)
{    
  as_huff_t  HuffMan={0};
  int i=0;

  if( argc != 3 )
  {   
    console_print("ERROR CMLD LINE USAGE : ./Executable   [Input File]   [OutputFile.bin]\n");
    return;
  }

  HuffMan.InFileDes  = FileOpening(argv[1],  READ_MODE_FILE);
  HuffMan.OutFileDes = FileOpening(argv[2], WRITE_MODE_FILE);

  if( -1 == HuffMan.InFileDes || -1 == HuffMan.OutFileDes)
    return;

  for(i=0;i<=0x7f ;i++)		//For Type Added to 1
    CountData[i].Type = i;

  ReadInputFile(HuffMan.InFileDes);
  
  for(i=0 ; i<=0x7f ; i++)
    if( 0 != CountData[i].Count )
      console_print("%3d, %3d : %5d\n",i, CountData[i].Type, CountData[i].Count );
 
  RearrangeData();
  console_print("After ReArranging\n");

  for(i=0 ; i<=0x7f ; i++)
    if( 0 != CountData[i].Count )
      console_print("%3d, %3d : %5d\n",i, CountData[i].Type, CountData[i].Count );

  HuffMan.StartIndex = GetStartingPoint();
  if( -1 == HuffMan.StartIndex )
  { 
    console_print("Error Occured in Getting StartIndex\n");
    return;
  }

  console_print("Start Index : %3d\n",HuffMan.StartIndex);

//  CreateBST( &HuffMan );

  /*
     if(!ParseInputData(&HuffMan))
     {
     console_print("Something went Wrong\n");
     return;
     }
     else
     HuffMan.TotChar--;



     for(i=0,printf("\n\n");i<HuffMan.TotChar;i++)
     printf("ASCII %3d--%d   \n",(int)HuffMan.characters[i],HuffMan.CountOfEachChar[i]);

     CopyBuffer(&HuffMan);

     ArrangeAssendingOrder(&HuffMan);
     for(i=0,printf("\n\n");i<HuffMan.TotChar;i++)
     printf("ASCII %3d\t\t%d\n",(int)HuffMan.characters[i],HuffMan.CountOfEachChar[i]);
     createBST(&HuffMan);
   */

}

int GetStartingPoint()
{
  int i=-1;
  for( i=0;i<=0x7f;i++)
    if( 0 != CountData[i].Count )
	return i;
  return i;
}

void RearrangeData()
{
  int i,j;
  for( i=0;i<=0x7f-1;i++)
    for( j=i+1 ; j<=0x7f ; j++)
       
      if( CountData[i].Count > CountData[j].Count )
	swap(i,j);
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
      (CountData[BufRead[i]].Count)++;
  }
  console_print("Done\n");
}

void CopyBuffer(as_huff_t  *HuffMan)
{
  HuffMan->Backup = malloc(sizeof(char)*(HuffMan->TotChar));
  strncpy(HuffMan->Backup,HuffMan->characters,HuffMan->TotChar);
}

void ArrangeAssendingOrder(as_huff_t *HuffMan)
{
  int i,j;
  char temp=0;
  for(i=0;i<(HuffMan->TotChar)-1;i++)
    for(j=i+1;j<(HuffMan->TotChar);j++)
      if( HuffMan->CountOfEachChar[i] > HuffMan->CountOfEachChar[j] )
      {
	HuffMan->CountOfEachChar[i] = HuffMan->CountOfEachChar[j] + HuffMan->CountOfEachChar[i] - (HuffMan->CountOfEachChar[j] = HuffMan->CountOfEachChar[i]);
	temp = HuffMan->characters[i];
      HuffMan->characters[i] = HuffMan->characters[j];
	HuffMan->characters[j] = temp;
      }
}

int FileOpening (char *Filename, int Flags)
{
  int FileDes;
  FileDes = open( Filename, Flags,0664);
  if ( -1 == FileDes )
  {
    console_print("ERROR IN FILE OPENING : %s ,REASON : %s\n",Filename,strerror(errno));
    return -1;
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

#if 0
bool ParseInputData (as_huff_t  *HuffMan)
{
  bool Gotit=false;
  int i=0;
  char ch=0;

  if ( HuffMan->characters == NULL)
  {   
    HuffMan->characters = calloc(1,sizeof(char));
    if ( HuffMan->characters == NULL)
    {
      console_print("Can't able to allocate memory for characters   %s\n",strerror(errno));
      return false;
    }
    printf("Entered into it\n");
  }

  if( HuffMan->CountOfEachChar == NULL)
  {
    HuffMan->CountOfEachChar = calloc(1,sizeof(int));
    if( HuffMan->CountOfEachChar == NULL )
    {
      console_print("Can't able to allocate memory for CountOfEachChar %s\n",strerror(errno));
      return false;
    }
    printf("Entered...\n");
  }

  (HuffMan->TotChar)++;
  while ( fread(&ch,sizeof(char),1,HuffMan->InFileDes) )
  {
    for(i=0,Gotit=false;i<HuffMan->TotChar;i++)
    {   
      if( ch == HuffMan->characters[i] )
      {
	Gotit = true;
	HuffMan->CountOfEachChar[i]++;
	break;
      }
    }

    if( Gotit == false )
    {
      HuffMan->characters      = realloc(  HuffMan->characters, (HuffMan->TotChar)*sizeof(char));
      HuffMan->CountOfEachChar = realloc(HuffMan->CountOfEachChar,(HuffMan->TotChar)*sizeof(int));
      if(HuffMan->CountOfEachChar == NULL || HuffMan->characters == NULL)
      {
	console_print("ERROR in elocating memory dynamic %s\n",strerror(errno));
	return false;
      }
      else
      {
	HuffMan->CountOfEachChar[(HuffMan->TotChar)-1] = 0;
	HuffMan->characters[(HuffMan->TotChar)-1] = 0;
      }
      HuffMan->characters[(HuffMan->TotChar)-1] = ch;
      (HuffMan->CountOfEachChar[(HuffMan->TotChar)-1])++;
      (HuffMan->TotChar)++;
    } 
  }
  return true;
}
#endif

