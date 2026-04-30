#include"sorting_algos.h"

#define MAX_ENTRIES 26

FILE *FileDes;

void main(int argc,char **argv)
{
#if 0
    int array[MAX_ENTRIES] = {0};
    Ip_rand(array, MAX_ENTRIES);
#else
    int array[MAX_ENTRIES] = {601,194,483,128,677,29,967,751,63,828,751,827,605,935,266,290,315,309,673,549,27,253,6544,976,367,76};
#endif

	/*
        selectionSort(array, MAX_ENTRIES);
        bubbleSort(array, MAX_ENTRIES);	
        heapSort(array, MAX_ENTRIES);
        quickSortPivot(array, MAX_ENTRIES);
        insertionSort(array, MAX_ENTRIES);
        mergeSort(array, MAX_ENTRIES);
    */
    console_print(array, MAX_ENTRIES, NULL);
    quickSort(array, MAX_ENTRIES);
    console_print(array, MAX_ENTRIES, NULL);
}

#if 0
void Read_file(int *array,int n)
{
    int i;
    for(i=0;i<n;i++)
	    fscanf(FileDes,"%d",&array[i]);
}

void Open_file(char *filename)
{
    FileDes = fopen(filename,"r+");
    if(FileDes == 0)
    {
	    printf("Unable to openfile ---->%s\n",filename);
	    exit(0);
    }
}
#endif

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

void selectionSort(int *array,int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
	    for(j=i+1;j<n;j++)
	        if(array[i]>array[j])		//Change should happen
		        swapArray(array,i,j);
}

void bubbleSort(int *array,int n)
{
    int i,j;
    for(i=0;i<n;n--,i=0)
	    for(j=i+1;j<n;j++,i++)
	        if(array[i] > array[j])
		        swapArray(array,i,j);
}

void insertionSort( int *array, int arrLen) {
    int Iterator, temp, index;

    for(index = 1; index<MAX_ENTRIES; index++) {
        temp = array[index];
        for( Iterator=index-1; Iterator>=0; Iterator--) {
            if(temp < array[Iterator]) {
                swap(&(array[Iterator]), &(array[Iterator+1]));
            } else {
                break;  
            }
        }
    }
}

/*  
    addrFinder() : gives address of requested Index.
    irrespective of 2 array's.
*/
int * addrFinder(int *arr1Ptr, int *arr2Ptr, int arrLen, int reqIndex) {
    int i, j, subArr1Len = 0, subArr2Len = 0;

    subArr1Len = arrLen / 2;
    subArr2Len = arrLen / 2;

    if(arrLen % 2)  // means arrLen is odd
        subArr2Len++;

    // reqIndex should be within the range.
    if (reqIndex >= arrLen) {
        printf("Requested Index %d is out of range %d\n", reqIndex, arrLen);
        return NULL;
    }

    if (reqIndex < subArr1Len) {
        return (arr1Ptr+reqIndex);
    } else {
        reqIndex = reqIndex - subArr1Len;
        return (arr2Ptr+reqIndex);        
    }
    return NULL;
}

void merge(int *arrayPtr, int *arr1Ptr, int *arr2Ptr, int arrLen) {
    int i, j, subArr1Len = 0, subArr2Len = 0;
    int *Ptr1 = NULL, *Ptr2 = NULL;

    subArr1Len = arrLen / 2;
    subArr2Len = arrLen / 2;
 
    if(arrLen % 2)  // means arrLen is odd
        subArr2Len++;

#if 0
    // Print sub array's before sorting.
    printf("BEF\t");
    for(i=0; i<subArr1Len; i++) {
        printf("%3d\t", arr1Ptr[i]);
    }
    printf("||\t");
    for(i=0; i<subArr2Len; i++) {
        printf("%3d\t", arr2Ptr[i]);
    }
    printf("\n\n");
 #endif

    // sorting 2 array's, techically into 1.
    // imaginary ga 2 array's ni, single array ga tiesukuni chesa.
    // addrFinder() naa sontha tellivitetallu tho chesina function.
    for(i=0; i < arrLen-1; i++) {
	    for(j=i+1; j < arrLen; j++) {
            Ptr1 = addrFinder(arr1Ptr, arr2Ptr, arrLen, i);
            Ptr2 = addrFinder(arr1Ptr, arr2Ptr, arrLen, j);
            if (Ptr1 != NULL && Ptr2 != NULL) {
	            if(*Ptr1 > *Ptr2) {
                    // Swapping data of 2 sub array's
		            swap(Ptr1, Ptr2);
                }
            } else {
                printf("Something went wrong while reading...\n");
                exit(0);
            }
        }
    }

    // Copy 2 sub array data into main array.
    for(i=0; i < arrLen; i++) {
        Ptr1 = addrFinder(arr1Ptr, arr2Ptr, arrLen, i);
        if (Ptr1 != NULL) {
            *(arrayPtr+i) = *Ptr1;
        } else {
            printf("Something went wrong in getting array addr\n");
            exit(0);
        }
    }
#if 0
    // Print if needed.
    printf("AFT\t");
    for(i=0; i < arrLen; i++) {
        printf("%3d\t", *(arrayPtr+i));
    }
    printf("\n\n");
#endif
}

void mergeSort(int *array, int arrLen) {
    int *arr1Ptr = NULL, *arr2Ptr = NULL;
    int i, j, subArr1Len = 0, subArr2Len = 0;

    sleep(1);
    subArr1Len = arrLen / 2;
    subArr2Len = arrLen / 2;
 
    if(arrLen % 2)  // means arrLen is odd
        subArr2Len++;

    printf("arrLen %d Arr1-%d Arr2-%d\n", arrLen, subArr1Len, subArr2Len);

    // Creating dynamic array
    arr1Ptr = calloc(subArr1Len, sizeof(int));
    arr2Ptr = calloc(subArr2Len, sizeof(int));

    // adding error check
    if (arr1Ptr == NULL || arr2Ptr == NULL) {
        printf("Error in creating dynamic array\n");
        exit(0);
    }

    // copy input array into dynamic array
    for( i=0; i<subArr1Len; i++) {
        arr1Ptr[i] = array[i];
        arr2Ptr[i] = array[i+subArr1Len];
    }
    // copying last byte
    if (subArr1Len != subArr2Len) {
        arr2Ptr[subArr2Len-1] = array[arrLen-1];
    }

    // Call recrively into multiple array's
    if (subArr1Len > 1 )
        mergeSort(arr1Ptr, subArr1Len);

    if (subArr2Len > 1)
        mergeSort(arr2Ptr, subArr2Len);

    // Here sorting happens.
    merge(array, arr1Ptr, arr2Ptr, arrLen);

    // Once merging is done, free dynamic array's.
    free(arr1Ptr);
    free(arr2Ptr);
}

void quickSort(int *array, int ArrLen) {
    int i=0, j=0, pivot = 0;

    pivot = ArrLen-1;                   // Consider pivot is last element index in array
    j =  0;                             // Consider index j, should be at starting.
    i = -1;                             // Consider index i, should be before j.

    printf("PIVOT Index %d | Value %d", pivot, array[pivot]);
    for( ; j <= pivot ; j++) {
        if( array[j] < array[pivot] ) {
            i++;                        // Increment i.
            swapArray(array, i, j);
        } else {
            // Ignore if >=
        }
    }
    i++;
    swapArray(array, i, pivot);
    console_print(array, ArrLen, "");

    if(i>1) {
        quickSort(array, i);
    }

    if(ArrLen-i-1 > 1) {
        quickSort(array+(i+1), ArrLen-i-1);
    }
}

void swapArray(int *array, int i, int j) {
    swap(&array[i], &array[j]);
}	

void swap(int *src1Ptr, int *src2Ptr) {
    int temp = 0;

    temp     = *src1Ptr;
    *src1Ptr = *src2Ptr;
    *src2Ptr = temp;
}

int power(int p,int q)
{
    int i,j,sum=1;
    for(i=0;i<q;i++)
	    sum*=p;
    return sum;
}

void heapSort(int *array,int n)
{
    int i,j,temp=n;

    for( ;temp ; )
    {
	    for(i=1;i<temp;i++)
	        if(array[0]<array[i])
		        swapArray(array,0,i);
	    swapArray(array,0,--temp);
    }
}

