

#ifndef __APP_HEADER_H__
#define __APP_HEADER_H__


#include <unistd.h>
#include<stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include<errno.h>
#include<string.h>
#include <string.h>
#include<stdint.h>
#include<errno.h>
#include<stdbool.h>
#include <sys/utsname.h>
#include<string.h>
#include<pthread.h>

#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>


#define LEFT_M		9
#define RIGHT_M		10
#define MIDDLE_M	12

#define LEFT		0x01
#define RIGHT		0x02
#define MIDDLE		0x04
#define MASK_SWITCHES	0X07



//void printBinary(uint8_t );
int ParseMouseData(uint8_t );



void CreateWindow();
void DestroyWindow();
void clearWindow();
int PrintString(char *);
void *sample(void *);


Bool SDL_XF86VidModeSetGamma(Display *, int, XF86VidModeGamma *);
void ControlBrightness(float *);
void GetMouseCoordinates(int *,int *);
#endif
