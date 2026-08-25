#include "./graph.h"

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
    graph_add_node('L');
    graph_add_node('M');


#if 0
    // make connections
    graph_add_edge('A', 'B', ONE_WAY, 1);
    graph_add_edge('B', 'C', ONE_WAY, 2);
    graph_add_edge('E', 'D', ONE_WAY, 3);
    graph_add_edge('D', 'E', ONE_WAY, 4);
    graph_add_edge('E', 'F', ONE_WAY, 5);
    graph_add_edge('A', 'E', TWO_WAY, 6);
    graph_add_edge('C', 'E', ONE_WAY, 7);
    graph_add_edge('A', 'I', ONE_WAY, 8);
    graph_add_edge('A', 'I', ONE_WAY, 9);
    graph_add_edge('J', 'D', TWO_WAY,10);
    graph_add_edge('I', 'I', ONE_WAY,11);
    graph_add_edge('A', 'I', TWO_WAY,12);
    graph_add_edge('F', 'H', TWO_WAY,13);
    graph_add_edge('C', 'G', TWO_WAY,14);
    graph_add_edge('B', 'F', TWO_WAY,15);
    graph_add_edge('A', 'K', TWO_WAY,16);
    graph_add_edge('L', 'K', TWO_WAY,17);
    graph_add_edge('J', 'I', ONE_WAY,18);
    graph_add_edge('I', 'K', TWO_WAY,19);
#else
    // make connections
    srand(getpid());
    graph_add_edge('A', 'B', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('B', 'C', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('E', 'D', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('D', 'E', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('E', 'F', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('A', 'E', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('C', 'E', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('A', 'I', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('A', 'I', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('J', 'D', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('I', 'I', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('A', 'I', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('F', 'H', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('C', 'G', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('B', 'F', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('A', 'K', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('L', 'K', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('J', 'M', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('J', 'I', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
    graph_add_edge('I', 'K', TWO_WAY, (rand()% EDGE_WEIGHT_MAX)+EDGE_WEIGHT_MIN);
#endif

    printf("\n\tInput Graph\n\n");
    graph_print();

    // Breath First Search
    // bfs('A');

    // Deapth First Search
    // dfs('E', 'I');

    // Prim's Algorithm
    prim('A');

    return;
}
