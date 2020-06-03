#include"rb_header.h"

void rotation(B **p,B **main)
{
/*	 *	*p = Manavaddu
	 *	temp = Daddie
	 *	temp->parent = Tatai
	 *	temp->parent->(left | | right) = Pedha nanna	
	We have to check,Weather to rotate left or right.	*/
	
	printf("In Rotation %d\n",(*p)->num);
	B *temp = (*p)->parent;
	if(temp != (*main) )											//Daddie should not be root
	{
		if(temp->right == *p)										//Tatai-Daddie   ---> Right
		{
			if    (  temp->parent->left == temp )						//Tatai-Daddie-child --> (Left ,Right)
			{
				printf("Rotation: 1st if Num: %d\n",(*p)->num);
				(*p)->parent = temp->parent;					
				(*p)->parent->left = (*p);
				(*p)->left = temp;
				temp->parent = (*p);
				temp->right = 0;									//----------------Changed to --> (Left,Left)
				Lrotate( (*p)->parent,main);
			}
			else if(temp->parent->right == temp)						//Tatai-Parent-child --> (Right,Right)
			{
				printf("Rotation: 2nd if Num : %d\n",(*p)->num);
				Rrotate((*p)->parent->parent,main);
			}
		}
		else if(temp->left == *p)									//Tatai-Parent   ---> Left
		{	
			if ( temp->parent->left == temp)							//Tatai-Parent-child --> (Left ,Left)
			{	
				printf("Rotation: 3rd if Num : %d\n",(*p)->num);
				Lrotate((*p)->parent->parent,main);
			}
			else if(temp->parent->right == temp)						//Tatai-Parent-child --> (Right,Left)
			{
				printf("Rotation: 4th if Num : %d\n",(*p)->num);
				temp->parent->right = (*p);
				(*p)->parent = temp->parent;
				(*p)->right = temp;
		//		(*p)->left = temp->left;
				temp->left = 0;
				temp->parent = (*p); 								 //----------------Changed to --> (Right,Right)
				Rrotate( (*p)->parent,main);
			}
		}
	}
	else 
		printf("Warning : rotation:Parent is the Root Node ----  Our Node %d\n",(*p)->num);				//TODO cannot be executed
}	

void Lrotate(B *ptr,B **main)								//LEFT-LEFT
{

  	B *Par = (ptr)->left;
	B *Chi = (ptr)->left->left;
	Par->parent = ptr->parent;									//Daddie Parent <-- Tatai->parent
	ptr->left=Par->right;										//This is Only diff
	Par->right = ptr;											//Tatai ni Right side shift

	if( (ptr)->parent)	{										//Tatai should not be root
		printf("Lrotate: Tatai ki daddie vunnaru\n");
		if( (ptr)->parent->left == (ptr) ) 
			 (ptr)->parent->left = Par;
		else
			 (ptr)->parent->right = Par;
	}
	else 
		*main = Par;											//Tatai == root node
		
	ptr->parent = Par;											
	if( ptr != *main )											//colours : 
		ptr->flag = 1;											//Change Tatai only if ,he is not root node
	Par->flag = 0;												//Parent Change to Black
}

void Rrotate(B *ptr,B **main)
{
	B *Par = ptr->right;
	B *Chi = ptr->right->right;
	Par->parent = ptr->parent;
	if(ptr->parent)
	{
		printf("Rrotate: Tatai ki Daddie present\n");
//		(ptr->parent->left == ptr) ? ( ptr->parent->left = Par) : (ptr->parent->right = Par);
		if(ptr->parent->left == ptr)
			ptr->parent->left = Par;
		else
			ptr->parent->right = Par;
	}
	else
		*main = Par;
	ptr->parent = Par;
	ptr->right = Par->left;
	Par->left = ptr;
	
	if(ptr != *main)											//Colours:
		ptr->flag =1;											//Change Tatai Only if he is not root node
	Par->flag = 0; 												//Parent to Black
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
	if(ptr->parent)										//Tatai vuntea
	{
	//	printf("check 1st if %d\n",p->num);
		if( ptr->flag == 1 )									//Daddie RED aithey
		{												//Means Parent & Child are "RED
	//		printf("check 2nd if %d\n",p->num);
			if( ptr->parent->left == ptr )					//Daddie LEFT lo vuntea
			{
	//			printf("check 3rd(1) if %d\n",p->num);
				if(ptr->parent->right)						//sibillings present
					if(ptr->parent->right->flag == 1 )			//Pedha nanna is RED , ( RIGHT lo vunnadu )
						return 1;							
			}
			else if( ptr->parent->right == ptr )				//Daddie right lo vunnadu
			{
	//			printf("check 3rd(2) if %d\n",p->num);
				if(ptr->parent->left)						//sibillings present
					if(ptr->parent-> left->flag == 1 )			//Pedha nanna is RED , ( LEFT lo vunnadu )
						return 1;
			}
		}
	}
//	printf("---\n");
	return 0;
}




/***************************************************************
/*	}
	else
	{	
		printf("Lrotate : Right lo data present\n");
		Par->parent = ptr->parent;
		Par->right = (ptr);											//Tatai ni Right side shift 	
		if( (ptr)->parent->left == (ptr) ) 
			 (ptr)->parent->left = Par;
		else
			(ptr)->parent->right = Par;
			
		(ptr)->left = Par->right;	
		ptr->parent = Par;
		if( (ptr) != *main )									//colours : Change Tatai only if ,he is not root node
			(ptr)->flag = 1;
		Par->flag = 0;	
	}
*************************************************************/

