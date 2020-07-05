#include"header_rain.h"

ak_int CmdLineParse(ak_int count,ak_char**string)
{
	ak_int rtn=0;
	if(count == 1)
		Help();
	else if(!strcmp("-h",string[1]) || !strcmp("--help",   string[1]))
		Help();
	else if(!strcmp("-v",string[1]) || !strcmp("--version",string[1]) )
		printf("\n\t%s.\n\n",version());
	else if(!strcmp("-d",string[1]) || !strcmp("--dev",    string[1]) ) 
		developer();
	else if(!strcmp("-r",string[1]) || !strcmp("--readme", string[1]) )
		readme();
	else if(atoi(string[1]) < 100)
		rtn = atoi(string[1]);
	else 
		printf("Wrong Input ,try [./rainHoles][--help].\n\n");
	return rtn;
}

void developer(void)
{
    printf("\n\n\n\tWelcome to Rain Holes Game\n\t\t\t\t-By Kothamasu.Aravind\n");
    printf("For how to use : check help message [./rainHoles] [--help]\n\n\nDeveloper details:-\n");
    printf("\tmail.id  : aravindkothamasu@gmail.com\n");
    printf("\tGithub   : https://github.com/Aravindkothamasu\n");
    printf("\tPhone    :  +91 9247727161.\n\n");
}

void readme(void)
{

}

void Help(void)
{
	system("clear");
	printf("\n\t\t\t\t\t\t\t  RAIN-HOLES-GAME\n\t\t\t\t\t\t\t  ---------------\n");
	printf("NAME\n     a.out - Rain Holes Game,fun game but tricky\n\nSYNOPSIS\n     #include\"header_rain.h\"\n\n     RainHoles - <executable> <args>\n     Usage:\t[./rainHoles] [args]\n\n");
	printf("DESCRIPTION\n     The \"rainHoles\" program is a old historic game in South Indian culture.Popularly called as \"VANNA GUNTALLA ATTA\".\n");
	printf("\nOPTIONS\n  Generic Program Information\n     -h, --help\n\t   Prints this help message.\n\n     -v,  --version\n\t   Prints the version of the program.\n\n     -d,  --dev\n\t   Gives the Developer Info.\n\n     -r,  --readme\n\t   Generates Program information.\n\n");
printf("     num\n\t   If user given Input as [./rainHoles][number],then \"number\" treated as no.of pichas for each guntha.\n\nAUTHOR\n     Wriiten by Aravind Kothamasu.\n\nREPORTING BUGS\n     ID : aravindkothamasu@gmail.com.\n\nVERSION\n     %s.\n\n",version());

}

ak_char* version(void)
{
	return "Version 1.2v Last modified time : 00:21 6th July 2020 Monday IST";
}
