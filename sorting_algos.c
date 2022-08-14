#include"header_sorting.h"
void main(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("Usage error [./a.out] [no.of i/p's] \n");
		return;
	}
	int n = atoi(argv[1]);
	int array[n];
	Open_file("data_Sorting");
	printf("Choice of Input\n1,File\t2,Manual\n");
	scanf(" %d",&choice);
	(choice==1)?Read_file(array,n):Ip_manual(array,n);

	/*
	 */
	/*		selectionSort(array,n);
			print(array,n);
			bubbleSort(array,n);
			print(array,n);	
			heapSort(array,n);*/
	print(array,n);
	quickSort(array,n);
	print(array,n);
	/*
	 */
}


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

void Ip_manual(int *array,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("Enter %d element -> ",i);
		scanf(" %d",&array[i]);
	}
}

void print(int *array,int n)
{
	printf("\n");
	for(int i=0;i<n;i++)
		printf("%d\t",array[i]);
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
		print(array,n);
	}
}



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
