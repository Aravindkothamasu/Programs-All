/////////////////////////////NEW.c//////////////////////////////

#include"header_rain.h"
ak_int bank[2]={0};

void main(ak_int argc,ak_char**argv)
{
        ak_data *hptr = 0;
        ak_int i,side,no=0;

        no=CmdLineParse(argc,argv);
        if(no == -1)
                return;
        for(i=0;i<14;i++)
                create(&hptr,no,i);	

        hptr->prev = LastNode(hptr);
        Print(hptr,0);

        if ((side = start())==-1)
                return;

        while(1)	
        {
                i = input(side);
                if(i=='q' || i=='Q')
                        ReDistribute(hptr,no);
                if(Distribute( hptr,i,side) == -1)
                    return;
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
        printf("\n\t\tTotal A/c Player 1 : %d\tPlayer 2 : %d\n\tRe-Arranging..\n",bank[0],bank[1]);
        sleep(4);                                                              //TODO : remove
        ReArrange(indicator,pichas);
}

/***************************************************************************/
/*          Re-Arranging all pichas to their respective hole's             */
/***************************************************************************/

void ReArrange(ak_data *hptr,ak_int pichas)
{
        ak_int i=0,j=7,Var;
        ak_data *temp=hptr;
        ak_int lag =-1;

        Print(hptr,0);
        (bank[0] <  pichas*7) ? (Maths(hptr,0,SideBlockIp(0),pichas)) : (Maths(hptr,1,SideBlockIp(1),pichas));
                                                                                //To know which side is less
        (bank[0] >= pichas*7) ? (Non_Lag(hptr,pichas,0)) : (Non_Lag(hptr,pichas,1));
                                                                                //To re-arrange non_lag player holes
/*
        printf("Can't able to fill in all holes of Player [%d] A/c : %d\n",lag+1,bank[lag]);
        Var=SideBlockInput();                                                   //To Which side u want to block 0(a-c) 1(e-g)
        Maths(hptr,lag,Var,pichas);
        */
}


/***************************************************************************/
/*      Maths func mains does the Re-distribution of pichas                */
/*    only for "lag player" and fill the remaining gunta's flag as 1       */
/***************************************************************************/

void Maths(ak_data* hptr,ak_int lag,ak_int StarSide,ak_int pichas)
{
                                 //TODO Remaining make as flag 1
    ak_int i,j,k;
    (StarSide) ? ( i = 0,j = other ) : ( i = other,j=6);
    for( ;i<=j;i++)
    {



}

/***************************************************************************/
/*      Non_lag func defines the Distribution of pichas                    */
/*      otherthan the lag one's and also making flag's  0                  */
/***************************************************************************/
void Non_Lag(ak_data* hptr,ak_int pichas,ak_int side)
{
    ak_int i,j,k;
    ak_data *p=hptr;
    if(side)
        p=SecondHalf(hptr);

    for(i=0;i<=6;i++)
    {
        bank[side] -= pichas;
        p->num = pichas;
        p->flag = 0;
        p=p->next;
    }
}

void Panchadam(ak_data*temp,ak_int pichas,ak_int side)
{
        temp->flag 	= 0;
        temp->num 	= pichas;
        bank[side] -= pichas;
}

/***************************************************************************/
/*      SideBlockIp func explains ,which side you want to block,           */
/*      the holes                                                          */  
/***************************************************************************/

ak_int SideBlockIp(ak_int player)
{
        ak_char ch=-1;
        printf("\n\tWhich side you want block of player [%d] [A-G](top-bottom)  : ",player);
        scanf(" %c",&ch);
        if( (ch>='a' && ch<='c') || (ch>='A' && ch<='C') )
                ch=0;
        else if( (ch>='e' && ch<='g') || (ch>='E' && ch<='G') )
                ch=1;
        else if( ch == '0' )
                ch -= 48;
        else if( ch == '1' )
                ch -= 48;
        else 
        {
                printf("\nTappu ichavu ra edhava [A-G]\n");
                return SideBlockIp(player);
        }
        return ch;
}

int Distribute(ak_data *hptr,ak_int index,ak_int side)
{
        ak_data *p = hptr,*q=SecondHalf(hptr),*indicator=0;
        ak_int i,j,k,temp = -1;

        //        system("clear");                                                        //TODO :  remove
        for(i=0;i<index;i++)
                (side) ? (q=q->next ) : ( p=p->next );

        temp = ((side)?(q->num):(p->num)); 					//storing no.into "temp" variable
        (side)?(q->num=0):(p->num=0);						//Making it as zero
        (side)?(indicator=q):(indicator=p);					//Feeding indicator as that pointer
        if(temp)
                while( temp )	
                {
                        NextNode(&indicator);
                        if(indicator->flag == 0)				//guntha is not star
                        {	
                                temp--;
                                indicator->num += 1;
                        }

                        if(temp == 0)						//guppeadu aipothey
                        {
                                NextNode(&indicator);			        //NextNode only gives non-star add's
                                temp = NextNum(indicator);		
                                indicator->num=0;
                                if(temp == 0)
                                {
                                        bank[side] += Occupy(indicator);
                                        Print(hptr,0);
                                   printf("\n\t\t\t-------> Round Completed Player [%d] : A/c : %d <------\n",side+1,bank[side]);
                                        usleep(100000);
                                        break;  
                                }
                        }
                }
        else
        {
                printf("Player [%d] of index [%d] has ZERO in this Gunta\n",index,side);
                sleep(5);
                return -1;
        }
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


///////////////////////////////////////////////////
