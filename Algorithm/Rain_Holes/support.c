#include"header_rain.h"
extern ak_char name[2][15];

/***************************************************************************/
/*  Command line parsing function describes that ,it will parse the        */
/*  elements,according to the input they given                             */
/***************************************************************************/
ak_int CmdLineParse(ak_int count,ak_char**string)
{
        ak_int rtn=-1;

        if(count == 4)
        {
                if(atoi(string[1]) < 100)
                    rtn = atoi(string[1]);
                strcpy(name[0],string[2]);
                strcpy(name[1],string[3]);
        }
        else if(count == 1)
                SmallHelp();
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

/***************************************************************************/
/*  Small help is shortform of help ,Usage message                         */
/***************************************************************************/
void SmallHelp()
{
        //TODO : short help
        printf("Usage : ./rainholes [no.of pichas] [Player 1 name] [Player 2 name]\n");
}

/***************************************************************************/
/*  Developer --> Says the about the legendary Developer                   */
/***************************************************************************/
void developer(void)
{
        printf("\n\n\n\tWelcome to Rain Holes Game\n\t\t\t\t-By Kothamasu.Aravind\n");
        printf("For how to use : check help message [./rainHoles] [--help]\n\n\nDeveloper details:-\n");
        printf("\tmail.id  : aravindkothamasu@gmail.com\n");
        printf("\tGithub   : https://github.com/Aravindkothamasu\n");
        printf("\tPhone    :  +91 9247727161.\n\n");
}

/***************************************************************************/
/*  README --> need to develop the readme()                                */
/*  It also generate the readme.md file                                    */
/***************************************************************************/
void readme(void)
{
    ak_int FileDes = open("README.md",O_RDWR|O_CREAT|O_TRUNC,0664);
    if(FileDes < 0)
    {
        printf("can't create README.md file\n");
        return;
    }
    ak_char *p="\t\t\t\t---------------------------------------------------------------------------------\n\t\t\t\t---------------------------    Rain Holes    ------------------------------------\n\t\t\t\t---------------------------------------------------------------------------------\n\t\t\t\t\t\t\t\t\t\t\tBy : -Kothamasu Aravind\n\n\tRain Holes Implementation :-\n\t---------------------------\n\t\t. Implmentation of Rain Holes in C language.\n\t\t. There is Cmd line parsing,given according to it.\n\t\t. There is a help session in the [./rainHoles][--help].\n\t\t. In order to give no.of pichas,u can give [./rainHoles][no.of pichas]\n\n.";

    if(write(FileDes,p,strlen(p)) < 0)
    {
        printf("Writting into README.md failed --> %s\n",strerror(errno));
        return;
    }
    else
        printf("\n\tREADME.md file created in PWD\n");
}

/***************************************************************************/
/* help() -> Prints the main help version of the rainHoles                 */
/***************************************************************************/
void Help(void)
{
        system("clear");
        printf("\n\t\t\t\t\t\t\t  RAIN-HOLES-GAME\n\t\t\t\t\t\t\t  ---------------\n");
        printf("NAME\n     a.out - Rain Holes Game,fun game but tricky\n\nSYNOPSIS\n     #include\"header_rain.h\"\n\n     RainHoles - <executable> <args>\n     Usage:\t[./rainHoles] [args]\n\n");
        printf("DESCRIPTION\n     The \"rainHoles\" program is a old historic game in South Indian culture.Popularly called as \"VANNA GUNTALLA ATTA\".\n");
        printf("\nOPTIONS\n  Generic Program Information\n     -h, --help\n\t   Prints this help message.\n\n     -v,  --version\n\t   Prints the version of the program.\n\n     -d,  --dev\n\t   Gives the Developer Info.\n\n     -r,  --readme\n\t   Generates Program information.\n\n");
        printf("     num\n\t   If user given Input as [./rainHoles][number],then \"number\" treated as no.of pichas for each guntha.\n\nAUTHOR\n     Written by Aravind Kothamasu.\n\nREPORTING BUGS\n     ID : aravindkothamasu@gmail.com.\n\nVERSION\n     %s.\n\n",version());

}

/***************************************************************************/
/*  version() ->Says the Software version developed by legendary C coder   */
/*          - Aravind Kothamasu                                            */
/***************************************************************************/
ak_char* version(void)
{
        return "Version 2.2v Last modified time : 21:23 16th July 2020 Thursday IST";
}

////////////////////////////////////////////////////////////////////
