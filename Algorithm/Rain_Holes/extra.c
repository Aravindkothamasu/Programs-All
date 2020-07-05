//////////////////////////EXTRA.c//////////////////////

#include"header_rain.h"

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
