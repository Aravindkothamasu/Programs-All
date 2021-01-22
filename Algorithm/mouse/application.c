
#include"app_header.h"												/// Includes  the custom created Header file.

static float Current = 0.5;											/// Current is a float variable for regulating the brightness index.


/*
 *  Integer RtnVal internal ga structure.
 *   BITS REPRESENTATION	76543210
 *				00000001 ---> 001 Indicates LEFT Click
 *				00000010 ---> 010 Indicates Middle Click
 *				00000011 ---> 100 Indicates RIGHT Click
 */

int ParseMouseData(uint8_t buff)										/// Parse Mouse Data ---> Func analyze the dat awhat ever data we recieved
{
    int RtnVal=0;												/// Need to return status.

    if ((buff >> 4 ) & 1)											/// We need only Clicks of mouse, so ignore data of moment mouse.
	return 0;
    else if ((buff >> 5 )  & 1)
	return 0;

    switch(buff)												/// switch case for which button is pressed
    {
	case LEFT_M:
	case LEFT  :												/// For LEFT
	    printf(" LEFT CLICK    : ");		
	    RtnVal = 0x1;											/// RETURN as 1
	    break;
	case MIDDLE_M:
	case MIDDLE :												/// For MIDDLE
	    printf(" MIDDLE CLICK  : RE-SETTING THE BRIGHTNESS   ");
	    RtnVal = 0x2;											/// RETURN as 2
	    break;
	case RIGHT_M:
	case RIGHT  :												/// For RIGHT
	    printf(" RIGHT CLICK   : ");
	    RtnVal = 0x4;											/// RETURN as 4
	    break;
	default :												/// Default case ,ignore default
	    break;
    }
    return RtnVal;												/// RETURN THE VALUE.
    /// Return Value can be ( 1, 2, 4 ).
}

int main(int argc,char **argv)											/// Here starts our main Application.	    
{
    int FileDes=0,bytes;											/// Creating Varible for File Descriptor (FileDes) and No.of bytes is recieved (bytes)
    int RtnVal=0,OffSet=0;											/// Decleration of Other Variables
    char buff[3]={0};												/// Creates the Buffer to store the read value.


    system("clear");												/// Clear the Output Screen
    printf("\n\n\t\t**********************************************************************\n");			/// Prints the Welcoming Message
    printf("\t\t********     USER SPACE APPLICATION TO READ MOUSE DATA	**********\n");
    printf("\t\t**********************************************************************\n\n\n");

    if(getuid())												/// Check whether current has ROOT access or not.
    {
	printf("\n\n\t APPICATION HAS NO ROOT ACCESS\n");							/// Print the Message
	printf("\t Add \"sudo\" BEFORE EXECUTABLE\n\n");    
	return 0;												/// return from here ,no need to proceed further.
    }

    FileDes = open("/dev/MOUSE",O_RDWR|O_SYNC);									/// Open the Character Special file.

    if( FileDes < 0)												/// Open() returns negative value on Error to opening the file.
    {
	printf("OPEN fails: %s\n",strerror(errno));								/// Prints the REASON to failed to open the special file
	return 0;												/// No need to continue further.
    }


    while(1)													/// infinite loop continusly looping for specific task 
    {														/// reads from the file and process the data recieved,and peform the brightness with that data.
	bytes = read(FileDes,buff,sizeof(buff));								/// read() reads the data from created file called /dev/MOUSE
														/// read will block till the new data is avaliable to read.
	if(bytes > 0)												/// What ever we read the data it mest be greater minumum of 1 Byte.
	{
	    RtnVal = ParseMouseData(buff[0]);									/// Parse the data what ever the recieved from read().
	    if(RtnVal)									    
	    {
		printf("\n");
		if(RtnVal == 0x1)										/// LEFT CLICK   --> 
		    Current += 0.1000;										///	    Increment the Variable
		else if(RtnVal == 0x2)										/// MIDDLE CLICK -->
		    Current = 0.5000;										///	    Set as MID as 0.5
		else if(RtnVal == 0x4)										/// RIGHT  CLICK --> 
		    Current -= 0.1000;										///	    Decrement the variable
		ControlBrightness(&Current);									/// Call the Brighness Control Func.
	    }	    
	}	
	bzero(buff,sizeof(buff));
    }														/// Non-exiting the loop.
}

