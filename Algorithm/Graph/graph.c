#include "./graph.h"


#define NODES_LEN    12

// Connection direction
#define ONE_WAY     false
#define TWO_WAY     true



bool Gph1[NODES_LEN][NODES_LEN];
char nodes[NODES_LEN] = {0};


void graph_init(int size) {
    int i, j;

    for(i=0; i<size; i++) {
        nodes[i] = 0;
        for(j=0; j<size; j++)
            Gph1[i][j] = 0;
    }
}

bool graph_add_node(char nodeName) {
    int i;

    // nodeName should be b/w range of 'A' to 'Z'
    if (nodeName < 'A' || nodeName > 'Z') {
        printf("Node name is out of range defined 'A' to 'Z' \n");
        return false;
    }

    // Check for nodeName is already present
    for(i=0; i < NODES_LEN; i++) {
        if (nodes[i] == nodeName) {
            printf("Node %c is already present at index: %d\n", nodeName, i);
            return false;
        }
    }

    // Insert nodeName into array.
    for(i=0; i < NODES_LEN; i++) {
        if (nodes[i] == 0) {
            nodes[i] = nodeName;
            return true;
        }
    }

    printf("Couldn't able to add Node: %c\n", nodeName);
    return false;
}

int graph_check_node(char node) {
    int i;
    for(i=0; i < NODES_LEN; i++) {
        if(nodes[i] == node)
            return i;
    }
    return -1;
}

/////////////////////////////////////////////////////////////

bool graph_add_edge(char src, char dest, bool direction) {
    // Checks for graph node is present or not
    if (-1 == graph_check_node(src) || -1 == graph_check_node(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Check for src and dest are not same
    if (src == dest) {
        printf("Src %c and Dest %c are can't be same\n", src, dest);
        return false;
    }

    // Create connection b/w src and dest
    Gph1[graph_check_node(src)][graph_check_node(dest)] = 1;

    // if it is Bi-Direction connection, connect the otherway around also.
    if (direction) {
        Gph1[graph_check_node(dest)][graph_check_node(src)] = 1;
    }

    return true;
}

bool graph_remove_edge(char src, char dest) {
    // Check for graph node is present or not
    if (-1 == graph_check_node(src) || -1 == graph_check_node(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Check for is there any connection b/w src -> dest
    if (!graph_check_edge(src, dest)) {
        printf("There is no connection b/w %c -> %c\n", src, dest);
        return false;
    }

    // Remove the connection
    Gph1[graph_check_node(src)][graph_check_node(dest)] = 0;
    return true;
}

bool graph_check_edge(char src, char dest) {
    // Check for graph node is present or not
    if (-1 == graph_check_node(src) || -1 == graph_check_node(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Connection is present, then it set to 1.
    return (Gph1[graph_check_node(src)][graph_check_node(dest)] == 1);
}

void graph_print() {
    int i, j;

    printf("\t ");
    for(i=0; i < NODES_LEN; i++) {
        // Check for non-empty node element in array
        if (nodes[i] != 0) {
            printf(" %c", nodes[i]);
        }
    }
    printf("\n");

    // Print connection data
    for (i=0; i < NODES_LEN; i++) {
        // Check for non-empty node element in array
        if (nodes[i] != 0) {
            printf("\t%c ", nodes[i]);
        }

        // Check for non-empty node element in array
        for(j=0; j < NODES_LEN; j++) {
            if (nodes[j] != 0 && nodes[i] != 0) {
                printf("%d ", Gph1[i][j]);
            }
        }
        printf("\n");
    }
}

/////////////////////////////////////////////////////////////

bool bfs(char src) {
    bool visitedNode[NODES_LEN] = {false};

    // Check for graph node is present or not
    if (-1 == graph_check_node(src)) {
        printf("Src %c is not present\n", src);
        return false;
    }

    // Making src or start node as visited.
    // int srcNode = graph_check_node(src);
    // visitedNode[srcNode] = true;

    while(false) {
        for(int i=0; i < NODES_LEN; i++) {

        }
    }

    return true;
}

/////////////////////////////////////////////////////////////


void main() {
    // Initiliase the graph
    graph_init(NODES_LEN);

    // Create nodes
    graph_add_node('A');
    graph_add_node('B');
    graph_add_node('C');
    graph_add_node('D');
    graph_add_node('E');
    graph_add_node('F');
    graph_add_node('G');
    graph_add_node('H');
    graph_add_node('I');
    graph_add_node('J');
    graph_add_node('K');
    graph_add_node('K');


    // make connections
    graph_add_edge('A', 'B', ONE_WAY);
    graph_add_edge('B', 'C', ONE_WAY);
    graph_add_edge('C', 'D', ONE_WAY);
    graph_add_edge('D', 'E', ONE_WAY);
    graph_add_edge('E', 'F', ONE_WAY);
    graph_add_edge('A', 'E', TWO_WAY);
    graph_add_edge('C', 'E', ONE_WAY);
    graph_add_edge('A', 'I', ONE_WAY);
    graph_add_edge('A', 'I', ONE_WAY);
    graph_add_edge('J', 'D', TWO_WAY);
    graph_add_edge('I', 'I', ONE_WAY);
    graph_add_edge('A', 'I', TWO_WAY);
    graph_add_edge('A', 'K', TWO_WAY);
    graph_add_edge('I', 'K', TWO_WAY);

    printf("\n\tInput Graph\n\n");
    graph_print();

    // Breath First Search
    //bfs('A');

    return;
}