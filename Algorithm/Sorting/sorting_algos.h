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
void quickSort(int *, int);
void insertionSort( int *, int);
void mergeSort(int *, int );
void merge(int *, int *, int *, int );
int * addrFinder(int *, int *, int , int);


// Miscellaneous
void console_print(int *,int, char*);


#endif