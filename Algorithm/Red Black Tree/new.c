////////////////////////////////////////////////////////////////////////////////////
#include"rb_header.h"

void main(int argc,char **argv)
{
	B *hptr = 0;														//TODO : '= 0' IMP
	Parsing(argc,argv,&hptr);
//	printf("\n\t----hptr = %x and *hptr = %x and &hptr = %x\n",hptr,*hptr,&hptr);
}

void Parsing(int argc,char **argv,B **hptr)
{
	int i;
	char ch=1;

	if(argc==2)
		 (argv[1][0] >= '0' && argv[1][0] <='9') ? 	my_random(hptr,atoi(argv[1])) : string(hptr,argv[1]);
	else if(argc>2)
		for(i=1;i<argc;i++)
			create(hptr,atoi(argv[i]));
	else														
		while(ch)
			( (ch=input(&i) ) == 'y') ? ( create(hptr,i) ,PrintAddr(hptr) ): ( create(hptr,i) ,PrintAddr(hptr) , ch =0);	
			
	if(*hptr)
	{
		PrintAddr(hptr);
		while(  NextEnti(hptr)  != 'e');
	}	
}

void string(B **hptr,char *p)
{
	if( !strcmp(p,"--help") || !strcmp(p,"-h"))
		helpMsg();
	else if( (p[0] == '-' ) && (p[1] == 'd' ) )
		Author();
	else if( (p[0] == '-' ) && (p[1] != 'd' ) )
	{	
		printf("\n\nUnknown Option....\n");
		helpMsg();
	}
	else
		File(hptr,p);
}

void File(B **hptr,char *FileName)
{
	int i;
	FILE  *FileDes = fopen(FileName,"r");
	if(!FileDes)
	{
		printf("Unable read the file : %s ,Reason :%s\n",FileName,strerror(errno));
		return;
	}
		
	while( fscanf(FileDes,"%d",&i) != EOF )
		create(hptr,i);
}

void my_random(B **hptr,int num)
{
	int *arr=malloc(sizeof(int)*num);
	int i;
	srand(getpid());
	
	for(i=0;i< num ;i++)														
		printf("%d\t",arr[i] = rand()%1000-500);
	printf("\n\n");	
	for(i=0;i< num ;i++)													
		create(hptr,arr[i] );
	free(arr);

}	
	
void CopytoFile(B **hptr)
{
	FILE * fd = 0;
	char buffer[150] = {0},Filename[20]={0};
	printf("Enter File name : ");
	scanf(" %[^\n]",Filename);
	strcat(Filename,".rb");
	if(!( fd = fopen(Filename,"w") ))
	{
		printf("\"%s\" file cannot able to create\n",Filename);
		return;
	}
	FilePrint(*hptr,fd);
	fprintf(fd,"\n\n");
	 FileAddr(hptr,fd);
}

void FilePrint(B *p,FILE *fp)
{
	if(p->left)
		FilePrint(p->left,fp);
	fprintf(fp,"%d\t",p->num);
	if(p->right)
		FilePrint(p->right,fp);
}

void FileAddr(B **p,FILE *fp)
{
	if((*p)->left)
		FileAddr(& ( (*p)->left ) ,fp);
fprintf(fp,"(Addr : %4x)( Cal: %x ) ( P :%x ) ( L : %x )  ( R : %x ) ( N : %d) (Flg: %d)\n",p,*p,(*p)->parent,(*p)->left,(*p)->right,(*p)->num,(*p)->flag);	
	if( (*p)->right)
		FileAddr(& ( (*p)->right),fp );	
}
	
int element(char *p)
{
	int temp;
	printf("Enter a element to %s  :  ",p);
	scanf(" %d",&temp);
	return temp;
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


void deletion(B **hptr,int value)										//TODO :
{
	int *Addr = Addr_search(hptr,value);
	B *node = (*Addr);
	if(!node)
	{
		printf("\n--> %d value not found\n",value);
		return;
	}

	printf("\n\t%d found ...Addr : %x , value in that %x\n",value,Addr,node);	
	if (!(node->right) && (!(node->left))  )
	{
		printf("No children\n");
		( node->parent->left == node ) ? ( node->parent->left = 0 ) :  (node->parent->right = 0);
		free(node);
	}
	else
	{
		
	
	
	
	}	
}

int * Addr_search(B **hptr,int value)
{
	if(!(*hptr))
		return 0;
	if( (*hptr)->num == value)
		return (int *)hptr;
		
	if((*hptr)->num > value)
		return Addr_search(&(*hptr)->left,value);
	else if((*hptr)->num < value)
		return Addr_search(&(*hptr)->right,value);
	
}

int search(B *hptr,int value)										//TODO :
{
	if(!hptr)
		return 0;
	if( hptr->num == value)
	{
		printf("---> %d <----- Value found\n",value);	
		return 1;
	}		
	if( hptr->num > value)
		return search(hptr->left,value);
	else if( hptr->num < value)
		return search(hptr->right,value);

}

void Author(void)
{
	system("clear");
	printf("\n\n\n\tWelcome to RedBlack Treeeeeeee\n\t\t\t\t-By Kothamasu.Aravind\n");
	printf("For how to use : check help message [./a.out] [--help]\n\n\nDeveloper details:-\n");
	printf("\tmail.id  : aravindkothamasu@gmail.com\n");
	printf("\tGithub   : https://github.com/Aravindkothamasu\n");
	printf("\tPhone    :  +91 9247727161.\n\n");
}

void helpMsg(void)
{
	printf("\n\n\t./a.out [options]\n  Options:\n");
	printf("    string\t  :  \"string\" is treated as file name and take the input from string eg : [./a.out] [Filename].\n");
        printf("    No.   \t  :  This represents,it will generate automaically those many random numbers and create tree eg : [./a.out] [10 random no's].\n");
        printf("    Line of No's  :  Create tree as u given the sequence of numbers eg : [./a.out] [15] [54] [5656] [256] .\n");
        printf("    Manual\t  :  if u want to give numbering one-by-one ,give simply [./a.out].\n");
        printf("    --help\t  :  To display the same page again.  (or) -h\n");
        printf("    --read\t  : \n");
}

char NextEnti(B **hptr)
{
	int i;
	char ch;
	printf("\n\t\t\t-------->   Tree Creation completed   <--------\n\tEnter Options : \n\td . Deletion\n\ts . Search\n\tc . Copy output into file \n\ty . Insertion\n\tp . Print No.s\n\ta . Print Addr's\n\te . exit\t\t    ---> (d/s/c/y/p/a/e)  :   ");
	scanf(" %c",&ch);
	switch (ch)
	{
		case 'd' : deletion(hptr,element("delete") );     break;
		case 's' : if( 0 == search(*hptr,i=element("search") ))
					printf("\t\t%d---> value not found\n",i);
			        break;
		case 'y' : create(hptr,element("create") );  PrintAddr(hptr); break;
		case 'c' : CopytoFile(hptr);   break;
		case 'p' : printf("\n\n"); print(*hptr); break;
		case 'a' : printf("\n\n"); PrintAddr(hptr); break;
		case 'e' : printf("\n\t\tExiting from program.....\n"); break;
		default :  printf("Wrong Option selected...\n");
				ch = 'e';
				break;
	}	
	return ch;
}

////////////////////////////////////////////////////////////////////////////////////
