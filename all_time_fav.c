#include<stdio.h>
#include<string.h>

void main()
{
	int i,j,k,l;
	char main[50]="today is also sunday",word[10]="also",replace[10]="tomorrow";

/*	printf("Enter the main String ...\n");
	scanf(" %[&\n]",main);
	printf("Enter th word tot replace in main string..\n");
	scanf(" %[^\n]",word);
	printf("Enter word to replace with ...\n");
	scanf(" %[^\n]",replace);*/
	
	for(i=0;main[i];i++)
	{
		if(word[0] == main[i])
			for(j=1;word[j];j++)
				if( word[j] != main[i+j] );

		if(strlen(word) == j)
		{
			if(strlen(word) > strlen(replace))
			{
				k = strlen(word) - strlen(replace);
				for( j=0 ; j<k ; j++ )
					for( l=i;l<=strlen(main);l++)
						main[l] = main[l+1];
			
			}
			else if(strlen(word) < strlen(replace))
			{
				k = strlen(replace) - strlen(word);
				for( j=0 ; j<k ; j++)
					for( l=strlen(main); l>=i ; l--)
						main[l+1] = main[l];
			}
			for(j=0;replace[j];j++)
				main[i+j] = replace[j];
	
			break;			
		}
	}	
	printf("%s\n",main);
}	
