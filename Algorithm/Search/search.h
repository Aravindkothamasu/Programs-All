#ifndef __SEARCH_H__
#define __SEARCH_H__

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

/// *********** Searching Algorithm's Prototype inclusion *********** ///
int linearSearch(int* , int , int );
int binarySearch(int* , int , int , int);
int ternarySearch(int* , int , int , int );


/// ****** Miscellaneous & Helper Function Prototype inclusion ****** ///
void console_print(int *,int , char *);
void Ip_rand(int *,int );
int indexGapBetween(int , int );


#endif