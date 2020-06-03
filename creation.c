#include"rb_header.h"
void create(B **ptr,int value)
{
	B *p=0;
	int val=0,*dad=0;
	B *AddPtr = 0;
//	printf("===== Value %d =====\n",value);									//TODO Last lo add cheyalli
	if(!(*ptr)) 
	{
		(*ptr) = calloc(1,sizeof(B));
		(*ptr)->num = value;
	}
	else
	{
		p = calloc(1,sizeof(B));
		p->num = value;	
		p->flag = 1;													// 1 = "RED"

		if (!(p->parent = AddPtr = (B *)filter(*ptr,0,value))) 					//Storing Parent Adds,if (Adds==0),then returns.(Repeated No.)
					return;	
		
		( AddPtr->num > value) ? (dad = (int *)&(AddPtr->left)) : (dad =(int *)&(AddPtr->right));			//From Parent to exact location
	
		*dad = p;
	//	PrintAddr(ptr);
		val = check(p);
	//	printf("Check %d\tvalue %d\n",val,p->num);
		if( val == 1 )											//(child && daddie && pedha nanna ) == RED
		{
			printf("If check == 1 is for %d\n",p->num);
			p->parent->parent->left->flag  = 0;					// daddie or pedha nanna ni BLACK
			p->parent->parent->right->flag = 0;					// daddie or pedha nanna ni BLACK
			if( p->parent->parent != (*ptr) ) 						//if Tatai is not ROOT
				p->parent->parent->flag     = 1;					//Tatai ni RED		
		}
		else	if( p->parent->flag == 1 )			{				// ( Child && daddie ) == RED ,and ! pedha nanna == BLACK	---> Rotation
				printf("rotation: %d\n",p->num);
				rotation(&p,ptr);
		}
		/*else if( val == 0 )
			printf("Nothing-----%d\n",p->num);	*/
	}
}

int * filter (B *ptr,int bit,int value)									//'0' will return when there is same no. placed again
{
	B *temp = ptr;
	if(temp)
		(bit == 1) ? (temp=temp->left) : ( (bit==2) ? (temp=temp->right ) : 0 ) ;
	if(temp)
	{	
		if  ( temp->num > value )
			return filter(temp,1,value);
		else if ( temp->num < value )
			return filter(temp,2,value);
		else
		{
			printf("Same No....%d\n",value);
			return 0;
		}
	}
	else
		return (int *)ptr;
}

