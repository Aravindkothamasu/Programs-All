#include "./graph.h"

graph Gph1[NODES_LEN][NODES_LEN];
char nodes[NODES_LEN] = {0};

////////////////        graph node functions         ////////////////////

void graph_init(int size) {
    int i, j;

    for(i=0; i<size; i++) {
        nodes[i] = 0;
        for(j=0; j<size; j++) {
            Gph1[i][j].connection = 0;
            Gph1[i][j].weight     = 0;
        }
    }
}

bool graph_add_node(char nodeName) {
    int i;

    // nodeName should be b/w range of NODE_NAME_MIN to NODE_NAME_MAX
    if (nodeName < NODE_NAME_MIN || nodeName > NODE_NAME_MAX) {
        printf("Node name is out of range defined '%c' to '%c' \n", NODE_NAME_MIN, NODE_NAME_MAX);
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

int graph_get_node_index(char nodeName) {
    int i;

    // check for input nodeName should be in within provided range.
    if(nodeName < NODE_NAME_MIN || nodeName > NODE_NAME_MAX) {
        printf("Get Node Index is out of range: %c <-> %c, but provided %2X\n", NODE_NAME_MIN, NODE_NAME_MAX, nodeName);
        return -1;
    }

    // Check for nodeName with the existing list
    for(i=0; i < NODES_LEN; i++) {
        if(nodes[i] == nodeName)
            return i;
    }
    return -1;
}

char graph_get_node_name(int index) {
    // Check if node is created or not.
    if(nodes[index] != 0)
        return nodes[index];

    return -1;
}

////////////////        graph vertex function         ////////////////////

bool graph_add_edge(char src, char dest, bool direction, int weight) {
    // Checks for graph node is present or not
    if (-1 == graph_get_node_index(src) || -1 == graph_get_node_index(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Check for src and dest are not same
    if (src == dest) {
        printf("Src %c and Dest %c are can't be same\n", src, dest);
        return false;
    }

    // weight should be greater than 0
    if( weight < EDGE_WEIGHT_MIN || weight > EDGE_WEIGHT_MAX ) {
        printf("Src %c and Dest %c, weight should be in range %d <-> %d\n", src, dest, EDGE_WEIGHT_MIN, EDGE_WEIGHT_MAX);
        return false;
    }

    // Create connection b/w src and dest
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)].connection = 1;
    // Adding weight
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)].weight     = weight;

    // if it is Bi-Direction connection, connect the otherway around also.
    if (direction) {
        Gph1[graph_get_node_index(dest)][graph_get_node_index(src)].connection = 1;
        // Adding weight
        Gph1[graph_get_node_index(dest)][graph_get_node_index(src)].weight     = weight;
    }

    return true;
}

bool graph_remove_edge(char src, char dest) {
    // Check for graph node is present or not
    if (-1 == graph_get_node_index(src) || -1 == graph_get_node_index(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Check for is there any connection b/w src -> dest
    if (!graph_check_edge(src, dest)) {
        printf("There is no connection b/w %c -> %c\n", src, dest);
        return false;
    }

    // Remove the connection
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)].connection = 0;
    // Clearing weight
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)].weight     = 0;
    return true;
}

bool graph_check_edge(char src, char dest) {
    // Check for graph node is present or not
    if (-1 == graph_get_node_index(src) || -1 == graph_get_node_index(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Connection is present, then it set to 1.
    return (Gph1[graph_get_node_index(src)][graph_get_node_index(dest)].connection == 1);
}

// Get the weight of the edge
int graph_get_weight_edge(int srcIdx, int destIdx) {
    // check for src and dest index are valid
    if (-1 == graph_get_node_name(srcIdx) || -1 == graph_get_node_name(destIdx)) {
        printf("SrcIdx %d or DestIdx %d are not a valid index\n", srcIdx, destIdx);
        return -1;
    }

    // check the edge is valid or not
    if (false == graph_check_edge( graph_get_node_name(srcIdx), graph_get_node_name(destIdx))) {
        printf("Src %c and Dest %c, there is no connected edge between\n", graph_get_node_name(srcIdx), graph_get_node_name(destIdx));
        return -1;
    }

    return Gph1[srcIdx][destIdx].weight;
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
                printf("%d ", Gph1[i][j].connection);
            }
        }
        printf("\n");
    }
}

