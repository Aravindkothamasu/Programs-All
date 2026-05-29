#include "search.h"


#define MAX_ENTRIES 28


void main ()
{
    int indexFound = 0;

#if 0
    int array[MAX_ENTRIES] = {0};
    Ip_rand(array, MAX_ENTRIES);
#else
    int array[MAX_ENTRIES] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
#endif
    console_print(array, MAX_ENTRIES, "");
    // indexFound = linearSearch(array, MAX_ENTRIES, 129);
    int i;

    for (i=0; i< MAX_ENTRIES; i++) {
        indexFound = ternarySearch(array, 0, MAX_ENTRIES-1, i);
        if(indexFound != -1) {
            printf("Value %2d || Index Found at %d\n\n", i, indexFound);
        }
    }
}

int indexGapBetween(int startIndex, int endIndex) {
    return endIndex - startIndex;
}

int ternarySearch(int* array, int startIndex, int endIndex, int value) {
    int mid1, mid2, i;

    mid1 = startIndex + ( endIndex - startIndex)/3;
    mid2 = endIndex - (endIndex - startIndex)/3;
    
    printf("Start: %d || end %d || mid1 %d || mid2 %d || value %d\n", startIndex, endIndex, mid1, mid2, value);

    if(array[mid1] == value) {                          // Value found at mid1 index
        return mid1;
    } else if(array[mid2] == value) {                   // Value found at mid2 index
        return mid2;
    } else if(array[mid1] > value) {                    // Value will be between startIndex <-> mid1
        if(indexGapBetween(startIndex, mid1-1) > 2)
            return ternarySearch(array, startIndex, mid1-1, value);
        else {
            // if len < 2, then traverse sequentially
            for(i=startIndex; i <= mid1-1; i++) {
                if (array[i] == value)
                    return i;
            }
        }
    } else if(array[mid2] < value) {                    // Value will be in mid2 <-> endIndex
        if(indexGapBetween(mid2+1, endIndex) > 2)
            return ternarySearch(array, mid2+1, endIndex, value);
        else {
            // if len < 2, then traverse sequentially
            for(i=mid2+1; i <= endIndex; i++) {
                if (array[i] == value)
                    return i;
            }
        }

    } else {                                            // Value will between mid1 <-> mid2
        if(indexGapBetween(mid1+1, mid2-1) > 2)
            return ternarySearch(array, mid1+1, mid2-1, value);
        else {
            // if len < 2, then traverse sequentially
            for(i=mid1+1; i <= mid2-1; i++) {
                if (array[i] == value)
                    return i;
            }
        }
    }

    return -1;
}

int binarySearch(int* array, int startIndex, int endIndex, int value) {
    int mid, i;

    mid = (endIndex-startIndex) / 2;
    mid += startIndex;
    //printf("StartIndex %2d || EndIndex %2d || Mid %2d\n", startIndex, endIndex, mid);
    if(array[mid] == value) {                                   // Value matches the mid point
        return mid;
    } else if(array[mid] < value) {                             // 2nd half string
        if(endIndex-mid > 2) {
            return binarySearch(array, mid+1, endIndex, value);
        } else {
            // printf("Comparing 2nd mid %2d || endIndex %2d\n", mid, endIndex);
            for(i=mid+1; i<=endIndex;i++) {
                if (array[i] == value)
                    return i;
            }
        }
    } else {                                                    // 1st half string
        if( mid-startIndex > 2) {
            return binarySearch(array, startIndex, mid-1, value);
        } else {
            // printf("Comparing 1st startIndex %2d || mid %2d\n", startIndex, mid);
            for(i=startIndex; i<mid;i++) {
                if (array[i] == value)
                    return i;
            }
        }
    }
    return -1;
}

int linearSearch(int* array, int ArrLen, int value) {
    int i;
    
    for(i=0; i < ArrLen; i++) {
        if(array[i] == value)
            return i;
    }

    return -1;
}

void Ip_rand(int *array,int EntryCount)
{
    int i;
    srand(getpid());
    for(i=0; i< EntryCount; i++)
    {
	    array[i] = rand()%1000;
    }
}

void console_print(int *array,int n, char *msg)
{
    if (msg != NULL)
        printf("\n%s\t", msg);
    else
        printf("\n");

    for(int i=0;i<n;i++)
	    printf("%03d\t",array[i]);
    printf("\n");
}

