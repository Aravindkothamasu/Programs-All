#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

typedef struct
{
    /* data */
    bool connection;
    int  weight;
}graph;


/// Node defined functions
void graph_init(int );
bool graph_add_node(char );
int graph_get_node_index(char );
char graph_get_node_name(int );

/// Edge defined functions  
bool graph_add_edge(char , char, bool, int);
bool graph_remove_edge(char , char );
bool graph_check_edge(char , char );
void graph_print();

/// Algo functions
bool bfs(char );
bool dfs(char , char );

// Supporting functions
bool allNodesVisited(bool *, int );
int addIntoStack(char *, int *, int );
int popUpFromStack(char *, int *);
void PrintStack(char *);


#endif