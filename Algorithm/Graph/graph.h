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

// This structure for Dijkstra Algo
typedef struct
{
    // check if node is visited or not
    bool visitedNode;
    // which node is previous node
    char previousNode;
    // length of shortest len
    int shortLen;
}DijkstraAlgo;


// Total nodeName length
#define NODES_LEN    6

// Connection direction
#define ONE_WAY     false
#define TWO_WAY     true

// Node name min & max requirements
#define NODE_NAME_MIN   'A'
#define NODE_NAME_MAX   'Z'

// Min and Max of edge weights
#define EDGE_WEIGHT_MIN     1
#define EDGE_WEIGHT_MAX    20

#define INCREMENT   true
#define DECREMENT   false

/// Node defined functions
void graph_init(int );
bool graph_add_node(char );
int graph_get_node_index(char );
char graph_get_node_name(int );

/// Edge defined functions  
bool graph_add_edge(char , char, bool, int);
bool graph_remove_edge(char , char );
bool graph_check_edge(char , char );
int graph_get_weight_edge(int , int );
void graph_print();

/// Algo functions
bool bfs(char );
bool dfs(char , char );
bool prim(char );
void topologicalSort();
void dijkstraSort(char );


// Supporting functions
bool allNodesVisited(bool *, int);
int addIntoStack(char *, int *, int, bool);
int popUpFromStack(char *, int *);
void PrintStack(char *);
int getLowerWeightIndex(int , bool *);
void dfs1(int , bool *, char *, int *);
bool checkAllNodesVisited();
void printSt();


#endif