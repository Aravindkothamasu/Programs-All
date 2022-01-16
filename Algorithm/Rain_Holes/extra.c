//////////////////////////EXTRA.c//////////////////////

#include"header_rain.h"
extern ak_int bank[2];
extern ak_char name[2][15];

/***************************************************************************/
/*      LastNode -> returns the last node of the index                     */
/***************************************************************************/
ak_data * LastNode(ak_data * hptr)
{
        ak_data * p = hptr;
        do{
                p =p ->next;
        }while(p->next != hptr);
        return p;
}

/***************************************************************************/
/*  Start : Who will start the game first either Player a/b                */
/***************************************************************************/
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

/***************************************************************************/
/*  Create the circular linked list                                        */
/***************************************************************************/
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

/***************************************************************************/
/*  Prints Only Addresses                                                  */
/***************************************************************************/
void PrintAddr(ak_data*hptr)
{
        ak_data *p = hptr;
        do{
                printf("prev %p Addr %p next %p num %d\n",
		    p->prev, p, p->next, p->num);
                p=p->next;
        }while(p !=hptr);
}	

/***************************************************************************/
/*  Add the data structure to the end of the list                          */
/***************************************************************************/
ak_data * AddEnd(ak_data*hptr)
{
        ak_data *p = hptr;
        do{
                p=p->next;
        }while(p->next != hptr);
        return p;
}

/***************************************************************************/
/*  SecondHalf -> Gives the Other Half starting Address                    */
/***************************************************************************/
ak_data * SecondHalf(ak_data *hptr)
{
        ak_data *p= hptr;
        ak_int   i;

        for(i=0;i<7;i++)
                p=p->next;
        return p;
}

/***************************************************************************/
/* my_Print defines the only the index and number                          */ 
/***************************************************************************/
void my_Print(ak_data*p)
{
        int i;	
        for(i=0;i<14;i++,p=p->next)
                printf("[%2d]-->  %d\n",p->index,p->num);
}

/***************************************************************************/
/*  Print the all the elements in the gunta's for both the elements        */
/***************************************************************************/
void Print(ak_data*hptr,ak_int num)	
{	
        ak_int   i;
        ak_data *p=hptr,*q=hptr;

        q=p->prev;
        system("clear");

        printf("\n\n\t\t-----  %s  ------\t\t\t\t\t\t\t-----  %s  ------\n\
               ***** A/c no:%3d *****\t\t\t\t\t\t\t*****  A/c no:%3d *****\n\n",name[0],name[1],bank[0],bank[1]);
        printf("\t\t-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-\n\n");	

        for(i=0;i<7;i++,p=p->next,q=q->prev)	
            if(p->flag )
                printf("\t%c       v   %s      *\t\t\t\t\t---\t\t\t\t%3d   %s   ^   %c\n"\
                                ,i+65,( ((num>>i)&1)?"-->":"   "),q->num,((num>>(13-i)&1)?"<--" :"   "),71-i);	
            else if(q->flag)
                printf("\t%c       v   %s    %3d\t\t\t\t\t---\t\t\t\t  *   %s    ^   %c\n"\
                                ,i+65,( ((num>>i)&1)?"-->":"   "),p->num,((num>>(13-i)&1)?"<--" :"   "),71-i);	
            else
                printf("\t%c       v   %s   %3d\t\t\t\t\t---\t\t\t\t%3d   %s   ^   %c\n"\
                                ,i+65,( ((num>>i)&1)?"-->":"   "),p->num,q->num,((num>>(13-i)&1)?"<--" :"   "),71-i);	
        printf("\n\t\t>->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->\n\n");	
        if(num)	
                sleep(1);	
}

/***************************************************************************/
/*  Input says about which index u want to select the gunta                */
/*  (A-G) and also (0-7) and you can also give 'q' for quit the game and   */
/*  do settlement and rearrange the game                                   */
/***************************************************************************/
ak_int input(ak_int side)
{
        ak_char ch=-1;
        if(side)
                printf("\n\t%s [A - G] /[q] for cancel:  ",name[1]);
        else
                printf("\n\t%s [A - G] /[q] for cancel :  ",name[0]);
        scanf(" %c",&ch);
        if (ch>='a' && ch<='g') 
                ch -= 97;
        else if (ch>='A' && ch<='G') 
                ch -= 65;
        else if(ch >= '0' && ch < '7')
                ch -= 48;
        else if(ch == 'q' || ch == 'Q')                                                 //TODO: need to quit 
                ch = 'q';
        else if ( (ch>='g' && ch<='z') || (ch>='G' && ch<='Z') || (ch>'7' ) )
              {
              printf("Wrong input.. try again..\n");
              ch = input(side);
              }   
        else
                printf("Input : Something else\n");
        return ch;	
}
///////////////////////////////////////////
