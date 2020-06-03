#include"rb_header.h"

void main(int argc,char **argv)
{
	B *hptr = 0;														//TODO : '= 0' IMP
	Parsing(argc,argv,&hptr);
	PrintAddr(&hptr);
}

void Parsing(int argc,char **argv,B **hptr)
{
	int i;
	char ch=1;
	srand(getpid());
	if(argc==2)
	{
		int *arr=malloc(sizeof(int)*atoi(argv[1]));
		for(i=0;i< atoi(argv[1]);i++)														
			printf("%d\t",arr[i] = rand()%1000-500);
		printf("\n\n");	
		for(i=0;i< atoi(argv[1]);i++)													
			create(hptr,arr[i] );
		free(arr);
	}
	else if(argc>2)
		for(i=1;i<argc;i++)
			create(hptr,atoi(argv[i]));
	else														
		while(ch)
			( (ch=input(&i) ) == 'y') ? create(hptr,i) : ( create(hptr,i) , ch =0);	
}
int height(B *ptr)
{
	if(!ptr)		
		return 0;
	int VarL = height(ptr->left);
	int VarR = height(ptr->right);
	return 1 + ( (VarL>VarR)?VarL:VarR );
}


void Flag_print(B *p)
{
	if(p->left)
		Flag_print(p->left);
	printf("%d\t%d\n",p->num,p->flag);		
	if(p->right)
		Flag_print(p->right);
}

void PrintAddr(B **p)
{
	if((*p)->left)
		PrintAddr(& ( (*p)->left) );
//	printf("(Addr : %x)( Cal: %x ) ( P :%x ) ( L : %x )  ( R : %x ) ( N : %d) (Flg: %d)\n",p,*p,(*p)->parent,(*p)->left,(*p)->right,(*p)->num,(*p)->flag);
	OnlyAdd(p);
	if( (*p)->right)
		PrintAddr(& ( (*p)->right) );
}

void OnlyAdd(B **p)
{
	printf("(Addr : %x)( Cal: %x ) ( P :%x ) ( L : %x )  ( R : %x ) ( N : %d) (Flg: %d)\n",p,*p,(*p)->parent,(*p)->left,(*p)->right,(*p)->num,(*p)->flag);
}

void print(B *p)
{
	if(p->left)
		print(p->left);
	printf("%d\t",p->num);		
	if(p->right)
		print(p->right);
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

/*
void deletion(B **hptr,int num)										//TODO :
{



}

int search(B **hptr,int num)										//TODO :
{

}*/
