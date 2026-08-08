#include "./graph.h"

// Total nodeName length
#define NODES_LEN    12

// Connection direction
#define ONE_WAY     false
#define TWO_WAY     true

// Node name min & max requirements
#define NODE_NAME_MIN   'A'
#define NODE_NAME_MAX   'Z'


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

/////////////////////////////////////////////////////////////

bool graph_add_edge(char src, char dest, bool direction) {
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

    // Create connection b/w src and dest
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)] = 1;

    // if it is Bi-Direction connection, connect the otherway around also.
    if (direction) {
        Gph1[graph_get_node_index(dest)][graph_get_node_index(src)] = 1;
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
    Gph1[graph_get_node_index(src)][graph_get_node_index(dest)] = 0;
    return true;
}

bool graph_check_edge(char src, char dest) {
    // Check for graph node is present or not
    if (-1 == graph_get_node_index(src) || -1 == graph_get_node_index(dest)) {
        printf("Src %c or Dest %c are not defined\n", src, dest);
        return false;
    }

    // Connection is present, then it set to 1.
    return (Gph1[graph_get_node_index(src)][graph_get_node_index(dest)] == 1);
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

////////////////        BFS         ////////////////////

// Check for all visited Nodes are not.
bool allNodesVisited(bool *visitedNode, int len) {
    int i;
    for(i=0; i < len; i++) {
        printf("%d ", *(visitedNode+i));
    }
    printf("\n");

    for(i=0; i < len; i++) {
        if (false == *(visitedNode+i)) {
            return false;
        }
    }
    return true;
}

/*  
*   Breadth for Search
*   traverse the all the nodes from the src, neighbour nodes make them visited.
*   traverse the next neighbour node, and ignore the already visited nodes.
*   Created FIFO array to get, which node the search should start next...
*   Once all nodes are visited. then it's Done.
*/
bool bfs(char src) {
    bool visitedNode[NODES_LEN] = {false};
    int  FIFO[NODES_LEN] = {0}, FIFO_RdIdx = 0, FIFO_WrIdx = 0;
    int srcNode, i;
    char dest;

    srcNode = graph_get_node_index(src);
    // Check for graph node is present or not
    if (-1 == srcNode) {
        printf("Src %c is not present\n", src);
        return false;
    } else {
        printf("Visited %c\n", src);
        // Making src or start node as visited.
        visitedNode[srcNode] = true;
        // Adding into FIFO array, with write index.
        FIFO[FIFO_WrIdx++] = srcNode;
    }

    while(true) 
    {
        // get the next src from the FIFO array.
        srcNode = FIFO[FIFO_RdIdx++];
        src = graph_get_node_name(srcNode);

        for(i=0; i < NODES_LEN; i++) {
            dest = graph_get_node_name(i);

            // Check b/w range nodeName is present or not
            if(dest < NODE_NAME_MIN || dest > NODE_NAME_MAX) {
                continue;
            }

            // Skip if src and dest are same
            if ( src == dest ) {
                continue;
            }

            // printf("SRC: %C || DEST: %c\n", src, dest);      // DEBUG
            // Check for connection is present or not
            if (graph_check_edge(src, dest) && !visitedNode[graph_get_node_index(dest)]) {
                printf("Visited %c\n", dest);
                // update the FIFO array, of new Visited Nodes.
                FIFO[FIFO_WrIdx++] = graph_get_node_index(dest);
                // Make visitedNode arr of this src is true.
                visitedNode[graph_get_node_index(dest)] = true;
            }
        }

        if (allNodesVisited(visitedNode, NODES_LEN)) {
            printf("All Nodes are visited Done...\n");
            break;
        }
        sleep(1);
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
    graph_add_node('L');
    graph_add_node('M');


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
    graph_add_edge('F', 'H', TWO_WAY);
    graph_add_edge('C', 'G', TWO_WAY);
    graph_add_edge('B', 'F', TWO_WAY);
    graph_add_edge('A', 'K', TWO_WAY);
    graph_add_edge('L', 'K', TWO_WAY);
    graph_add_edge('I', 'K', TWO_WAY);

    printf("\n\tInput Graph\n\n");
    graph_print();

    // Breath First Search
    bfs('A');

    return;
}