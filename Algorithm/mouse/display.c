#include"app_header.h"											    /// Include Custom Created Header File.

void ControlBrightness(float* BrightVal)								    /// ControlBrightness Func --> Controls the Brightness of the screen.
{   
    int DispVal  =  *BrightVal * 100;									    /// Converting Brightness into decimal and multipling with 100
    int X=0,Y=0;
    Display *display;											    /// Creating a variable for display

    XF86VidModeGamma brightness;									    /// Declaring a variable for x86 display gamma func.
    brightness.red    = *BrightVal;									    /// Set the contrast for RED colour.
    brightness.blue   = *BrightVal;									    /// Set the contrast for BLUE colour.
    brightness.green  = *BrightVal;									    /// Set the contrast for GREEN colour.

    display=XOpenDisplay(NULL);										    /// Opens the Display (init)
    if (display)											    /// Check xopenDisplay () is success or not.
    {
        if( DispVal >= 10 && DispVal <= 100 )								    /// Our Dispval should be Greater than or equal to 10 and not exceed 100
        {
            SDL_XF86VidModeSetGamma(display,0,&brightness);						    /// Feed the Values of Brighness to the Func.
	    GetMouseCoordinates(&X,&Y);
            printf("Current Brightness Level --> [ %2.2f ]  COORDINATES X : Y [%d:%d]  \n",*BrightVal,X,Y); /// Display the Status.
        }
        else												    /// If Brightness value is not in RANGE.
        {   
            if( DispVal >= 110)								
            {
                printf("\t BRIGHTNESS VALUE [%d] EXCEDDED",DispVal);					    /// Displays Appropriate messaage
                *BrightVal = 0.9000;									    /// Resetting the Brightness value to MAX.
            }
            else
	    {
                printf("\t BRIGHTNESS VALUE IS TOO BELOW");						    /// Displays Appropriate message.
		*BrightVal = 0.1;									    /// Resetting the Brightness Value to MIN.
	    }
            printf("   Re-Setting the Brightness to [ %2.2f ]\n",*BrightVal);
        }
    }
    else												    /// If can't open XOpenDisplay().then
        printf("Control Brightness Display Open Failed\n");						    /// Prints Error Message
    XCloseDisplay(display);										    /// Close the Display()
}

