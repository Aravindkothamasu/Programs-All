////////////////////////////////////////////////////////////////////////////////////

#include"rb_header.h"
void create(B **ptr,int value)
{
	B *p=0;
	int val=1,*dad=0,i=1;
	B *AddPtr = 0,*temp = 0;
	
//	printf("===== Value %x =====\n",ptr);									//TODO Last lo add cheyalli
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
		temp = p;					
		while(val)
		{
			val = check(temp);
			temp = Violations(temp,ptr,val);
			if(!temp)
				break;
		}
	}
}

B * Violations(B *p,B **ptr,int val)
{
	B *temp = 0;
	if(val == 1)
		temp = AllRed(p,ptr);
	else if(val == 2)
		temp = rotation(p,ptr);
	return temp;
}



B* AllRed(B *p,B**ptr)
{
	p->parent->parent->left->flag  = 0;					// daddie or pedha nanna ni BLACK
	p->parent->parent->right->flag = 0;					// daddie or pedha nanna ni BLACK
	if( p->parent->parent != (*ptr) ) 						//if Tatai is not ROOT
		p->parent->parent->flag     = 1;					//Tatai ni RED		
	return (p->parent->parent);
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

int check(B *p)
{
	/*
	 *	p = Manavaddu
	 *	ptr = Daddie
	 *	ptr->parent = Tatai
	 *	 ptr->parent->(left | | right) = Pedha nanna
	 */			 
	B *ptr = p->parent;
	if(!ptr || !(p->flag) )
		return 0;
	if(ptr->parent)										//Tatai vuntea
	{
		if( ptr->flag )									//Daddie RED aithey
		{												//Means Parent & Child are "RED
			if( ptr->parent->left == ptr )						//Daddie LEFT lo vuntea
			{
				if(ptr->parent->right)						//sibillings present
					if( ptr->parent->right->flag )			//Pedha nanna is RED , ( RIGHT lo vunnadu )
						return 1;							
			}
			else if( ptr->parent->right == ptr )				//Daddie right lo vunnadu
			{
				if(ptr->parent->left)						//sibillings present
					if( ptr->parent-> left->flag )			//Pedha nanna is RED , ( LEFT lo vunnadu )
						return 1;
			}
		}
	}
		
	if(p->parent->flag)
		return 2;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////
