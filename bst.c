#include"bst_header.h"				//try i/p 23 65 1 5435 2 67
void main(int argc,char **argv)
{
	B *p = 0;			//Marchipoku 0 pettadam
	int i;
	if(argc>1)
		for(i=1; i<argc ; i++)	
			create(&p , atoi(argv[i]) );
	else
		while( 'y' == input(&i) )
			create(&p,i);
	print(p);	
}

void create(B **ptr,int value)
{
	B *p=0;
	int *AddPtr = 0;
	if(!(*ptr))
	{
		(*ptr) = calloc(1,sizeof(B));
		(*ptr)->num = value;
	}
	else
	{
		AddPtr = filter(ptr,value);
		if(!AddPtr)
			return;
		p = calloc(1,sizeof(B));
		p->num = value;
		p->parent = (B *)AddPtr;	
		*AddPtr = (void *)p;
	}
}

int * filter (B** ptr,int value)
{
	if(*ptr)
	{
		if  ( (*ptr)->num > value )
			return filter( &(*ptr)->left,value);
		else if ( (*ptr)->num < value )
			return filter( &(*ptr)->right,value);
		else
		{
			printf("Same No....%d\n",value);
			return 0;
		}
	}
	else
		return (int *)ptr;
}

char input(int *p)
{	
	char ch;
	printf("\nEnter Value  :  ");
	scanf(" %d",p);
	printf("\nDo u need to continue  :  ");
	scanf(" %c",&ch);
	return ch;

}

void print(B *p)
{
	if(p->left)
		print(p->left);
	printf("%d\t",p->num);		
	if(p->right)
		print(p->right);
}

