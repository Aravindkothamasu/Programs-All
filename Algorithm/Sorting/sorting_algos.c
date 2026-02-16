#include"sorting_algos.h"

#define MAX_ENTRIES 25

FILE *FileDes;

void main(int argc,char **argv)
{
#if 0
    int array[MAX_ENTRIES] = {0};
    Ip_rand(array, MAX_ENTRIES);
#else
    int array[MAX_ENTRIES] = {601,194,483,128,677,29,967,751,828,751,827,605,935,266,290,315,309,673,549,27,253,6544,976,367,76};
#endif

    /*
       selectionSort(array,n);
       console_console_print(array,n);
       bubbleSort(array,n);
       console_console_print(array,n);	
       heapSort(array,n);
     */

    for(int i=0; i< MAX_ENTRIES; i++)
	    printf("%03d\t", i);
    //console_print(array, MAX_ENTRIES);
    printf("\n");
    quickSortPivot(array, MAX_ENTRIES);
    console_print(array, MAX_ENTRIES);
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

void console_print(int *array,int n)
{
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
		        swap(array,i,j);	
}

void bubbleSort(int *array,int n)
{
    int i,j;
    for(i=0;i<n;n--,i=0)
	    for(j=i+1;j<n;j++,i++)
	        if(array[i] > array[j])
		        swap(array,i,j);
}


void swap(int *array,int i,int j)
{
    array[i] = array[j] + array[i] - (array[j] = array[i]);
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
		        swap(array,0,i);
	    swap(array,0,--temp);
    }
}

#if 0
void quickSort(int *array,int n)
{
    int pivot=rand()%n,left=0,right=n-1;
    printf("pivot = %d\n",pivot);
    printf("array[pivot] = %d\n",array[pivot]);

    while(pivot != left || pivot != right )
    {
	    if( array[pivot] < array[right] )
	        right--;
	    else if(array[pivot] > array[right])
	    {
	        pivot = right;
	        swap(array,pivot,right);
	    }

	    if( array[pivot] < array[left] )
	        left++;		
	    else if ( array[pivot] > array[left] )
	    {
	        pivot = left;
	        swap(array,pivot,left);
	    }
	    console_print(array,n);
    }
}
#else

int quickSortPivot(int *arr, int arrLen) {
    //return 0;       // TODO: For now selecting pivot as 0 index.
    int low, high;

    // FIXME: Below logic will work only work, when pivot is 0 index.
    low   = 0;
    high  = arrLen - 1;

    low = quickSort(arr, low, high);
    console_print(arr,MAX_ENTRIES);
    while(1) {
        printf("=======================\n");
        quickSort(arr, 0, low-1);
        printf("=======================\n");
        quickSort(arr, low+1, high); 
        break;
    }
}

int quickSort(int *arr, int low, int high) {
    int pivot = low;

    printf("Iteration Low %d High %d**\n", low, high);
    low++;

    while(low < high) {        
        console_print(arr, MAX_ENTRIES);

        while(arr[pivot] > arr[low])
            low++;

        while(arr[pivot] <= arr[high])
            high--;

        printf("*** LOW %d HIGH %d\n", low, high);
        if (low<high)
            swap(arr, low, high);
    }
    swap(arr, pivot, high);

    printf("***** LOW %d HIGH %d PIVOT %d\n", low, high, pivot);
    return high;
}
#endif
/*
   void heapSort(int *array,int n)
   {
   int level=0,i,j=0,pow,sum=0,temp=n;
   int first,second;
   printf("\tno.of nodes = %d\n",n);
   while(temp>0)
   temp -= (1<<level++);
   level--;

   printf("level = %d\n",level);
   temp = level;

//	while (level)
first = power(2,level)-1;
second = power(2,level-1)-1;
for( i=0 ;i<4  ;i++,first++,second++)
{
if( array[first] > array[second] )
swap(array,first,second);
print(array,n);
if( array[++first] > array[second] )
swap(array,first,second);
print(array,n);
}
///////////////////////////////////////////////////////////////////////////////////////////////	
if( array[ power(2,level) ] < array[ power(2,level-1)-1 ] )
swap(array,power(2,level),power(2,level-1)-1);
print(array,n);

if( array[ power(2,level)+1 ] < array[ power(2,level-1) ] )
swap(array,power(2,level)+1,power(2,level-1));
print(array,n);


if( array[ power(2,level)+2 ] < array[ power(2,level-1) ] )
swap(array,power(2,level)+2,power(2,level-1));
print(array,n);

if( array[ power(2,level)+3 ] < array[ power(2,level-1)+1 ] )
swap(array,power(2,level)+3,power(2,level-1)+1);
print(array,n);

if( array[ power(2,level)+4 ] < array[ power(2,level-1)+1 ] )
swap(array,power(2,level)+4,power(2,level-1)+1);
print(array,n);

if( array[ power(2,level)+5 ] < array[ power(2,level-1)+2 ] )
swap(array,power(2,level)+5,power(2,level-1)+2);
print(array,n);
}
/////////////////////////////////////////////////////////////////////////////////////////////		
}	
 */
