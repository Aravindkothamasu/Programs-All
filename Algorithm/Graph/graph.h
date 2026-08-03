#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>


/// Node defined functions
void graph_init(int );
bool graph_add_node(char );
int graph_get_node_index(char );
char graph_get_node_name(int );

/// Edge defined functions  
bool graph_add_edge(char , char, bool );
bool graph_remove_edge(char , char );
bool graph_check_edge(char , char );
void graph_print();

/// Algo functions
bool bfs(char );


#endif