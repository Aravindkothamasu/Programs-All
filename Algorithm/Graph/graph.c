#include "./graph.h"


#define GRAPH_SIZE    5

// Connection direction
#define ONE_WAY     false
#define TWO_WAY     true



int Gph1[GRAPH_SIZE][GRAPH_SIZE];
char nodes[GRAPH_SIZE] = {0};


void graph_init(int size) {
    int i, j;

    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
            Gph1[i][j] = 0;
}

void graph_add_node(char nodeName) {
    int i;

    for(i=0; i < GRAPH_SIZE; i++) {
        if (nodes[i] == 0) {
            nodes[i] = nodeName;
            return;
        }
    }
}

int graph_check_node(char node) {
    int i;
    for(i=0; i < GRAPH_SIZE; i++) {
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

    // if it is Bi-Direction connection, connect the otherway around.
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

    return (Gph1[graph_check_node(src)][graph_check_node(dest)] == 1);
}

void graph_print() {
    int i, j;

    printf("\t  %c %c %c %c %c\n", nodes[0], nodes[1], nodes[2], nodes[3], nodes[4]);

    for (i=0; i<GRAPH_SIZE; i++) {
        printf("\t%c ", nodes[i]);
        for(j=0; j < GRAPH_SIZE; j++) {
            printf("%d ", Gph1[i][j]);
        }
        printf("\n");
    }
}

void main() {

    graph_init(GRAPH_SIZE);

    graph_add_node('A');
    graph_add_node('B');
    graph_add_node('C');
    graph_add_node('D');
    graph_add_node('E');

    printf("\tNode A | Index: %d\n", graph_check_node('A'));
    printf("\tNode B | Index: %d\n", graph_check_node('B'));
    printf("\tNode C | Index: %d\n", graph_check_node('C'));
    printf("\tNode D | Index: %d\n", graph_check_node('D'));
    printf("\tNode E | Index: %d\n", graph_check_node('E'));
    printf("\tNode F | Index: %d\n", graph_check_node('F'));

    graph_add_edge('A', 'B', ONE_WAY);
    graph_add_edge('B', 'C', ONE_WAY);
    graph_add_edge('C', 'D', ONE_WAY);
    graph_add_edge('D', 'E', ONE_WAY);
    graph_add_edge('E', 'F', ONE_WAY);
    graph_add_edge('A', 'E', TWO_WAY);

    /*
    printf("%d\n", graph_check_edge('A', 'B'));
    printf("%d\n", graph_check_edge('B', 'C'));
    printf("%d\n", graph_check_edge('C', 'D'));
    printf("%d\n", graph_check_edge('D', 'E'));
    */
    graph_print();
    return;
}