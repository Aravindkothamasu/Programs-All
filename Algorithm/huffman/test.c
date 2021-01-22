#include"huffman_header.h"
#if 0


void main(int argc,char **argv)
{
    int FileDes = open("sample",O_RDONLY),count=0,i=0;
    char buffer[10]={0};
    count = read(FileDes,buffer,sizeof(buffer));
    printf("Array %s\n",buffer);
    for(i=0;i<count;i++)
        printf("ASCII %d\t%c\n",(int)buffer[i],buffer[i]);
    printf("Count -> %d\n",count);



    count = read(FileDes,buffer,sizeof(buffer));
    printf("\nArray %s\n",buffer);
    for(i=0;i<count;i++)
        printf("ASCII %d\t%c\n",(int)buffer[i],buffer[i]);
    printf("Count -> %d\n",count);
}
#endif

#include <stdio.h>
int main()
{
    int i;
    char ch;
    FILE *fp;
    fp=fopen("a.txt","w+");
    for(i=0;i<128;i++)
    {
        fprintf(fp,"%c",i);
    }
    fseek(fp,0,SEEK_SET);
    while(fread(&ch, sizeof(char), 1, fp))
        printf("%d\n",ch);
    return 0;
}
