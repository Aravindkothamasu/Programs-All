
#include"Huffman_Header.h"
#define SIZE_BUFFER 10


void main(int argc , char **argv)
{    
  as_huff_t  HuffMan={0};
  int i=0;

  if( argc != 3 )
  {   
    console_print("ERROR CMLD LINE USAGE : ./Executable   [Input File]   [OutputFile.bin]\n");
    return;
  }
  FileOpening(argv[1],&(HuffMan.InFileDes),"r");
  FileOpening(argv[2],&(HuffMan.OutFileDes),"w");


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

void FileOpening (char *Filename,FILE **FilePtr,char *flags)
{
  *FilePtr = fopen(Filename,flags);
  if ( *FilePtr == NULL )
  {
    console_print("ERROR IN FILE OPENING : %s ,REASON : %s\n",Filename,strerror(errno));
    exit(1);
  }
}


void FramingData( int Line, const char *Func, const char *File, const char *format, ...)
{								    
  char Buffer[500]={0};
  va_list args;
  va_start( args, format);					    
  sprintf( Buffer, "#%s %s() [%d] : ", File, Func, Line);	    
  vsprintf( &Buffer[strlen(Buffer)], format, args);		    
  va_end(args);	
  printf("%s\n", Buffer);
}

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

