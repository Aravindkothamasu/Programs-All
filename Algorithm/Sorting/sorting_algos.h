#ifndef __SORTING_ALGOS_H__
#define __SORTING_ALGOS_H__

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>


// Function prototype inclusion
void Ip_rand(int *,int );
void swapArray(int *, int, int);
void swap(int *, int *);

// Sorting Algo's Prototype inclusion
void selectionSort(int *,int );
//void quickSort(int *,int );
int quickSort(int *, int , int );
int quickSortPivot(int *, int );
void insertionSort( int *, int);


// Miscellaneous
void console_print(int *,int );


#endif