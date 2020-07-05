//////////////////////////EXTRA.c//////////////////////

#include"header_rain.h"
extern ak_int bank[2];
ak_data * LastNode(ak_data * hptr)
{
	ak_data * p = hptr;
	do{
		p =p ->next;
	}while(p->next != hptr);
	return p;
}

ak_int start(void)	
{	
	ak_int   side=-1;	
	ak_char ch;	
	printf("\tWho will start first  ---> ( a/b ) <---   :   ");	
	scanf(" %c",&ch);	
		
	switch (ch)	
	{	
		case 'A' :
		case '1' :	
		case 'a' : side = 0; break;	
		
		case 'B' :
		case '2' : 	
		case 'b' : side = 1;  break;	
		default  : printf("\n\tEesari vollu dhagara petuuni ivvu....\n");	
				side = -1;	
	}
	return side;	
}

void create(ak_data **hptr,ak_int value,ak_int index)
{
	ak_data *p =0;
	if( *hptr == 0)
	{
		*hptr = calloc(1,sizeof(ak_data));
		(*hptr)->index 	= index;
		(*hptr)->num 	= value;
		(*hptr)->next 	= *hptr;
	} 
	else
	{	
		p = calloc(1,sizeof(ak_data));
		p->num 	   	= value;
		p->next    	= *hptr;
		p->index   	= index;
		p->prev    	= AddEnd(*hptr);
		p->prev->next 	= p;
	}
}

void PrintAddr(ak_data*hptr)
{
	ak_data *p = hptr;
	do{
		printf("prev %x Addr %x next %x num %d\n",(ak_uint64)p->prev,(ak_uint64)p,(ak_uint64)p->next,p->num);
		p=p->next;
	}while(p !=hptr);
}	

ak_data * AddEnd(ak_data*hptr)
{
	ak_data *p = hptr;
	do{
		p=p->next;
	}while(p->next != hptr);
	return p;
}

ak_data * SecondHalf(ak_data *hptr)
{
	ak_data *p= hptr;
	ak_int   i;
	
	for(i=0;i<7;i++)
		p=p->next;
	return p;
}

void my_Print(ak_data*p)
{
    int i;	
    for(i=0;i<14;i++,p=p->next)
        printf("[%d]-->  %d\n",p->index,p->num);

}

void Print(ak_data*hptr,ak_int num)	
{	
    ak_int   i;
    ak_data *p=hptr,*q=hptr;

    q=p->prev;
    system("clear");					//TODO clear	

    printf("\n\n\t\t-----  Player 1  ------\t\t\t\t\t\t\t-----  Player 2  ------\n\
            \t***** A/c no: %d *****\t\t\t\t\t\t\t*****  A/c no: %d  *****\n\n",bank[0],bank[1]);
    printf("\t\t-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-\n\n");	

    for(i=0;i<7;i++,p=p->next,q=q->prev)	
        printf("\t%c       v   %s   %d\t\t\t\t\t---\t\t\t\t%d   %s   ^   %c\n"\
                ,i+65,( ((num>>i)&1)?"-->":"   "),p->num,q->num,((num>>(13-i)&1)?"<--" :"   "),71-i);	
    printf("\n\t\t>->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->\n\n");	
    if(num)	
        sleep(1);	
}

ak_int input(ak_int side)
{
    ak_char ch=-1;
    if(side)
        printf("\n\tPlayer 2 [A - G] /[q] for cancel:  ");
    else
        printf("\n\tPlayer 1 [A - G] /[q] for cancel :  ");
    scanf(" %c",&ch);

    if (ch>='a' && ch<='g') 
        ch -= 97;
    else if (ch>='A' && ch<='G') 
        ch -= 65;
    else if(ch >= '0' && ch <= '7')
        ch -= 48;
    else if(ch == 'q' && ch == 'Q')
        ch = -1;
    else if ( (ch>='g' && ch<='z') || (ch>='G' && ch<='Z') || (ch>'7' ) )
    {
        printf("Wrong input.. try again..\n");
        ch = input(side);
    }
    else
        printf("Input : Something else\n");
    printf(" %d...\n",ch);
    return ch;	
}
/*
ak_int   BankStatus(ak_data*hptr,ak_int   flag)
{
	ak_data *p = hptr;
	ak_int   i,j,value=0;
	if(!flag)
		for(i=0;i<7;i++)	
			p=p->next;
	for(i=0;i<7;i++)
		value += p->bank;
	return value;
}
*/
///////////////////////////////////////////