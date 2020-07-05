/////////////////////////////NEW.c//////////////////////////////

#include"header_rain.h"
ak_int bank[2]={0};

void main(ak_int argc,ak_char**argv)
{
    ak_data *hptr = 0;
    ak_int i,side;

    if(argc != 2)
    {
        printf("\tUsage : [ ./a.out ] [ no.of pichas ]\n");		//TODO : update help message
        return;
    }

    for(i=0;i<14;i++)
        create(&hptr,atoi(argv[1]),i);	

    hptr->prev = LastNode(hptr);
    Print(hptr,0);

    if ((side = start())==-1)
        return;

    while(1)	
    {
        i = input(side);
        if(i=='q' || i=='Q')
            ReDistribute(hptr,atoi(argv[1]));
        Distribute( hptr,input(side),side);	
        side = !side;
    }
}

void ReDistribute(ak_data* indicator,ak_int pichas)
{
    ak_int i,j;
    for(j=0;j<2;j++)
        for(i=0;i<7;i++)
        {
            bank[j] += indicator->num;
            indicator->num=0;	
            indicator=indicator->next;
        }
    printf("Total A/c Player 1 : %d\tPlayer 2 : %d\n\tRe-Arranging..\n",bank[0],bank[1]);
    sleep(4);
    ReArrange(indicator,pichas);
}

void ReArrange(ak_data *hptr,ak_int pichas)
{
    ak_int i=0,j=7,Var;
    ak_data *temp=hptr;

    if(bank[0] < pichas*7)
    {
        printf("Can't able to fill in all tot -> 1 <-: %d\n",bank[0]);
        Print(hptr,0);
        Var=SideBlockInput();
		(Var)?(i=0,j=Maths(0,pichas,Var) ):(j=7,i=Maths(0,pichas,Var) );
					//TODO Remaining make as flag 1
    }

    for( ;i<j;i++,temp=temp->next)
        Panchadam(temp,pichas,0);

    temp=SecondHalf(hptr);
    i=0;j=7;

    if(bank[1] < pichas*7)
    {
        printf("Can't able to fill in all tot -> 2 <-: %d\n",bank[1]);		
        Print(hptr,0);
        Var = SideBlockInput();
		(Var)?(j=Maths(1,pichas,Var) ):(i=Maths(1,pichas,Var) );
			//TODO Remaining make as flag 1
    }
    for( ;i<j;i++,temp=temp->next)
        Panchadam(temp,pichas,1);
}

ak_int Maths(ak_int side,ak_int pichas,ak_int BlockSide)
{
	ak_int temp = bank[side],i=6;
	
	while(bank[side] < i*pichas)
		i--;
	if(BlockSide)
		i=i-5456;												//TODO : Change here
	return i;
}

void Panchadam(ak_data*temp,ak_int pichas,ak_int side)
{
    temp->flag 	= 0;
    temp->num 	= pichas;
    bank[side] -= pichas;
}

ak_int SideBlockInput(void)
{
    ak_char ch=-1;
    printf("\n\tWhich side you want to block [A-G] : ");
    scanf(" %c",&ch);
    if( (ch>='a' && ch<='c') || (ch>='A' && ch<='C') )
        ch=0;
    else if( (ch>='e' && ch<='g') || (ch>='E' && ch<='G') )
        ch=1;
    else 
	{
        printf("\nTappu ichavu ra edhava [A-G]\n");
		return SideBlockInput();
	}
    return ch;
}

void Distribute(ak_data *hptr,ak_int index,ak_int side)
{
    ak_data *p = hptr,*q=SecondHalf(hptr),*indicator=0;
    ak_int i,j,k,temp = -1;

    system("clear");
    for(i=0;i<index;i++)
        (side) ? (q=q->next ) : ( p=p->next );

    temp = ((side)?(q->num):(p->num)); 					//storing no.into "temp" variable
    (side)?(q->num=0):(p->num=0);						//Making it as zero
    (side)?(indicator=q):(indicator=p);					//Feeding indicator as that pointer

    while( temp )	
    {
        NextNode(&indicator);
        if(indicator->flag == 0)						//guntha is not star
        {	
            temp--;
            indicator->num += 1;
        }

        if(temp == 0)									//guppeadu aipothey
        {
            NextNode(&indicator);						//NextNode only gives non-star add's
            temp = NextNum(indicator);		
            indicator->num=0;
            if(temp == 0)
            {
                bank[side] += Occupy(indicator);
                printf("Voka sari aipoindhi bank = %d side %d\n",bank[side],side);
                sleep(3);
                Print(hptr,0);
                break;
            }
        }



        my_Print(hptr);										//TODO remove all these
        printf("\n\n");	
        printf("In hand %d\n",temp);
        system("clear");
    }
}

void my_Print(ak_data*p)
{
    int i;	
    for(i=0;i<14;i++,p=p->next)
        printf("[%d]-->  %d\n",p->index,p->num);

}

ak_int Occupy(ak_data *indicator)
{
    ak_int temp = -1,tempIndex=-1;

    do{
        indicator = indicator->next;
    }while( (indicator->flag) == 1);				//looping upto gunta without "star"

    temp = indicator->num;						//storing that variable into that
    indicator->num = 0;						//Making as ZERO
    tempIndex = indicator->index;

    while(indicator->index != Vennaka(tempIndex))					//looping for other side
        indicator = indicator->next;

    temp += indicator->num;
    indicator->num=0;
    return temp;
}

ak_int Vennaka(ak_int Value)
{
    return (13-Value);
}

void NextNode(ak_data **indicator)					//For NextNode ,otherthan "star"
{
    do{
        (*indicator) = (*indicator)->next;
    }while((*indicator)->flag == 1);
}

ak_int NextNum(ak_data*p)
{
    return (p->num);
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
///////////////////////////////////////////////////
