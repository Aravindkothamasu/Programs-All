#ifndef __SORTING_ALGOS_H__
#define __SORTING_ALGOS_H__

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>


/// Node defined functions
void graph_add_node(char );
int graph_check_node(char );

/// Edge defined functions  
void graph_init(int );
bool graph_add_edge(char , char, bool );
bool graph_remove_edge(char , char );
bool graph_check_edge(char , char );
void graph_print();



#endif