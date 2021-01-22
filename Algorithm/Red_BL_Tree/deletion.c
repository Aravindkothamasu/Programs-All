/////////////////////////////DELETION.c///////////////////////////////
#include"rb_header.h"

void deletion(B **hptr,int element)
{
	char result=0;
	int *Pointer = Addr_search(hptr,element);
	B*data = (B*)(*Pointer),*sister=0,*child=0;
	
	if(!data)
	{
		printf("%d Not found..\n",element);
		return;
	}
	printf("%d...Found at %x value at %x\n",element,Pointer,data);
	
	
	if(data->left && data->right)				//Contains 2 childs ,deletion can't possible
		printf("\tContains both child's ,deletion can't possible\n");
	else if(data == *hptr) 					//Root node should be deleted
		//printf("\tNode need to delete is root node\n");
		RootNodeDelete(data,hptr);
	else if( (!data->left) && (!data->right) )		//no chldren present 
	{
		printf("\tNo children are present\n");		
		(data->parent->left == data )?(sister = data->parent->right): (sister = data->parent->left);
		ParsingSibillingRelation( SibillingStatus(sister),data,hptr);	
		( data->parent->left == data ) ? (data->parent->left = 0) : (data->parent->right = 0);
		free(data);
	}	
	else							//pakka child is present
	{
		(data->parent->left == data )?(sister = data->parent->right): (sister = data->parent->left);
		( data->left )? (child = data->left):(child = data->right);
//		printf("\tIt has %s Child \n",(data->left)?"left":"right");
														
		if(data->flag != child->flag)
		{
			printf("Both are diff clr flags ---> Par %d\tChi %d\n",data->num,child->num);
			data->num = child->num;
			data->flag  = 0;
			( data->left == child ) ? (data->left = 0) : (data->right = 0);
			free(child);
		}
		else if(!data->flag && !child->flag)
		{
			printf("Both black colour flags --> Par %d\tChi %d\n",data->num,child->num);
			ParsingSibillingRelation( SibillingStatus(sister),data,hptr);
			( data->parent->left == data ) ? (data->parent->left = child) : (data->parent->right = child);
			child->parent = data->parent;
			free(data);
			
		}
		else if(data->flag && child->flag)
			printf("RED colour flags NODE that want to delete, and it's child --> Par %d\tChi %d\n",data->num,child->num);
	}
}

void RootNodeDelete(B*root,B**hptr)
{
	(root->left)?(*hptr = root->left) : (*hptr = root->right);
	(*hptr)->flag = 0;
	(*hptr)->parent = 0;
}

void ParsingSibillingRelation(char result,B*node,B**hptr)
{
	B* sister = ( (node->parent->left == node) ? ( node->parent->right ) : (node->parent->left));
	B* SisChi= 0,*temp = 0;
	
	if(sister == 0)	
		printf("Sibilling not present\n");										//TODO :handle sibilling is not present
	else if( result >> 4 &1)	{
		printf("\tRight\n");
		SisChi = sister->right;	
	}
	else if(result >> 2 &1)	{
		printf("\tLeft\n");
		SisChi = sister->left;
	}
	else if( (result >> 2 &1) && (result >> 4 &1) )
		printf("Sibilling has both childrens--> sib  %d  Chi Le %d,Right %d\n",sister->num,sister->left->num,sister->right->num);
	else
	{
		printf("There is no child for sister\n");								
		temp = calloc(1,sizeof(B));											//Create a dummy child with value as -1 
		temp->parent = sister;												// and setting as left to sister
		sister->left = temp;
		temp->num = -1;
		SisChi = temp;
	}
	
	
	if(sister != 0)	
		if ( result&1 )														//Sibilling present 
		{
			if( result &2 )														//sibilling is RED
			{
				if(SisChi->flag)													//R - R
					printf("ParsingSibillingRelation : R - R Alert\n");
				else if(!(SisChi->flag))												//R - B
					rotation(SisChi,hptr);	
			}
			else																//sibilling is BLACK
			{
				if(SisChi->flag)		{											//B - R
					SisChi->flag = 0;
					rotation(SisChi,hptr);
				}
				else if(!(SisChi->flag))												//B - B
				{		
					SibillingChildBothRBlack(node,hptr);
				}
			}
		}
}

void SibillingChildBothRBlack(B*node,B**hptr)
{
	if(node == *hptr)
	{
		node->flag = 0;
		return;
	}
	
	B*sister = ( (node->parent->left == node ) ? ( node->parent->right ) : (node->parent->left) );
	if(!sister) 
		return;
	sister->flag = 1;
	(sister->parent->flag) ? (sister->parent->flag = 0) : (sister->parent->flag = -1);
	if(sister->parent->flag == -1)
		SibillingChildBothRBlack(sister->parent,hptr);
}

char SibillingStatus(B *node)
{
	char temp = -1;
	if(node)														//sibilling present
	{
		(node->flag) ? (temp = 3 ) : (temp = 1);						//sibilling is  1 , red || 2, black
		
		if(node->left)
			(node->left->flag) ?  (temp |= (3<<2) ) : (temp |= (1<<2) );
		if(node->right)
			(node->right->flag) ? (temp |= (3<<4) ) : (temp |= (1<<4) );
	}
	
	return temp;	
}
