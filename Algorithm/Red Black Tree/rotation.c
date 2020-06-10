////////////////////////////////////////////////////////////////////////////////////
#include"rb_header.h"

B* rotation(B *p,B **main)
{
/*	 *	*p = Manavaddu
	 *	temp = Daddie
	 *	temp->parent = Tatai
	 *	temp->parent->(left | | right) = Pedha nanna	
	We have to check,Weather to rotate left or right.	*/
	
//	printf("In Rotation %d\n",p->num);
	B *temp = p->parent;
	if(temp != (*main) )											//Daddie should not be root
	{
		if(temp->right == p)										//Tatai-Daddie   ---> Right
		{
			if    (  temp->parent->left == temp )						//Tatai-Daddie-child --> (Left ,Right)
			{
	//			printf("Rotation: 1st if Num: %d\n",p->num);
				p->parent = temp->parent;					
				p->parent->left = p;
				p->left = temp;
				temp->parent = p;
				temp->right = 0;									//----------------Changed to --> (Left,Left)
				Lrotate( p->parent,main);
				return p;
			}
			else if(temp->parent->right == temp)						//Tatai-Parent-child --> (Right,Right)
			{	
				Rrotate(p->parent->parent,main);
				return p->parent;
			}
		}
		else if(temp->left == p)									//Tatai-Parent   ---> Left
		{	
			if ( temp->parent->left == temp)							//Tatai-Parent-child --> (Left ,Left)
			{
				Lrotate(p->parent->parent,main);
				return ( p->parent );
			}
			else if(temp->parent->right == temp)						//Tatai-Parent-child --> (Right,Left)
			{
		//		printf("Rotation: 4th if Num : %d\n",p->num);
				temp->parent->right = p;
				p->parent = temp->parent;
				p->right = temp;
				temp->left = 0;
				temp->parent = p; 								 //----------------Changed to --> (Right,Right)
				Rrotate( p->parent,main);
				return p;
			}
		}
	}
	else 
		printf("Warning : rotation:Parent is the Root Node ----  Our Node %d\n",p->num);				//TODO cannot be executed
	
  	return 0;
}	

void Lrotate(B *ptr,B **main)									//LEFT-LEFT
{

  	B *Par = (ptr)->left;
	B *Chi = (ptr)->left->left;
	Par->parent = ptr->parent;									//Daddie Parent <-- Tatai->parent
	ptr->left=Par->right;										//This is Only diff
	if(ptr->left)
		ptr->left->parent = ptr;
	Par->right = ptr;											//Tatai ni Right side shift
	
	if( (ptr)->parent)	{										//Tatai should not be root
//		printf("Lrotate: Tatai ki daddie vunnaru\n");
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
//		printf("Rrotate: Tatai ki Daddie present\n");
		if(ptr->parent->left == ptr)
			ptr->parent->left = Par;
		else
			ptr->parent->right = Par;
	}
	else
		*main = Par;
	
//	Par->left->parent = ptr;
	ptr->parent = Par;
	ptr->right = Par->left;
	if(ptr->right)
		ptr->right->parent = ptr;
	Par->left = ptr;
	
	if(ptr != *main)											//Colours:
		ptr->flag =1;											//Change Tatai Only if he is not root node
	Par->flag = 0; 												//Parent to Black
}


//////////////////////////////////////////////////////////////////////////////////
