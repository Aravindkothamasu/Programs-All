#include "Huffman_Header.h"

void main (int argc, char **argv)
{
	CmdLineCheck(argc);
	
	
	
	
	
}

int CmdLineCheck(int argc)
{
  if( argc != 2 )
  {   
    console_print("ERROR CMLD LINE USAGE : ./Decode   [Input File.bin]\n");
	exit(0);
  }
}