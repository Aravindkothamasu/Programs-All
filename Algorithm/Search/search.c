#include "search.h"


#define MAX_ENTRIES 26


void main ()
{
    int indexFound = 0;

#if 0
    int array[MAX_ENTRIES] = {0};
    Ip_rand(array, MAX_ENTRIES);
#else
    int array[MAX_ENTRIES] = {601,194,483,128,677,29,967,751,63,828,751,827,605,935,266,290,315,309,673,549,27,253,6544,976,367,76};
#endif
    console_print(array, MAX_ENTRIES, "");
    indexFound = linearSearch(array, MAX_ENTRIES, 129);
    if(indexFound != -1){
        printf("Index Found at %d\n", indexFound);
    }
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

