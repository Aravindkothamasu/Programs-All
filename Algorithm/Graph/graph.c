#include "./graph.h"

// Total nodeName length
#define NODES_LEN    13

// Connection direction
#define ONE_WAY     false
#define TWO_WAY     true

// Node name min & max requirements
#define NODE_NAME_MIN   'A'
#define NODE_NAME_MAX   'Z'


graph Gph1[NODES_LEN][NODES_LEN];
char nodes[NODES_LEN] = {0};


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

/////////////////////////////////////////////////////////////

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
    if( weight < 0 ) {
        printf("Src %c and Dest %c, provided weight should be > 0\n", src, dest);
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

////////////////        DFS         ////////////////////

void PrintStack(char *StackPtr) {
    int i;
    for(i=0; i < NODES_LEN; i++) {
        if (*(StackPtr+i) != 0)
            printf("%C ", *(StackPtr+i));
    }
    printf("\n");
}

int addIntoStack(char *StackPtr, int *WrIdxPtr, int NodeIdx ) {
    int i;

    // Check for WrPtrIdx should not exceed NODES_LEN
    if (*WrIdxPtr >= NODES_LEN) {
        printf("Error in Adding into Stack: %c\n", graph_get_node_name(NodeIdx));
        return -1;
    }

    // check for 'NodeIdx' is already in StackPtr.
    for (i=0; i<NODES_LEN; i++) {
        if (*(StackPtr+i) == graph_get_node_name(NodeIdx)) {
            return 0;
        }
    }

    // Add NodeIdx into the stack.
    *(StackPtr+*WrIdxPtr) = graph_get_node_name(NodeIdx);
    // Increment the pointer.
    (*WrIdxPtr)++;

    // Print the stack
    PrintStack(StackPtr);
    return 1;
}

int popUpFromStack(char *StackPtr, int *WrIdxPtr) {
    int Rtn = -1;

    // Decrement the Write Index.
    (*WrIdxPtr)--;

    // Store the removing element
    Rtn = *(StackPtr+*WrIdxPtr);
    printf("PopUp Element : %C\n\n", Rtn);

    // replace the removed element with 0
    *(StackPtr+*WrIdxPtr) = 0;

    // print the stack
    PrintStack(StackPtr);
    return Rtn;
}

bool dfs(char src, char dest) {
    int srcNodeIdx = -1, destNodeIdx = -1;
    char Stack[NODES_LEN] = {0};
    int i=0, j=0, WrIdx = 0;

    // Check for src graph node is present or not
    srcNodeIdx = graph_get_node_index(src);
    if (-1 == srcNodeIdx) {
        printf("Src '%c' is not present\n", src);
        return false;
    }

    // Check for dest graph node is present or not
    destNodeIdx = graph_get_node_index(dest);
    if(-1 == destNodeIdx) {
        printf("Dest '%c' is not present\n", dest);
        return false;
    }

    // Add src into starting stack
    Stack[WrIdx++] = src;

    // Starting indicator is src
    i = srcNodeIdx;

    while(true) {
        if (j < NODES_LEN) {
            // Print only 'j' is only valid.
            printf("\nSrc-%C || Dest-%C\n", graph_get_node_name(i), graph_get_node_name(j));
        }

        for ( ;j < NODES_LEN; j++) {
            // Ignore 'j' is src
            if(j == srcNodeIdx) {
                continue;
            }

            // Check for connection.
            if (graph_check_edge(graph_get_node_name(i), graph_get_node_name(j))) {
                // Check for reached destination or not
                if (graph_get_node_name(j) == dest) {
                    addIntoStack(Stack, &WrIdx, j);
                    printf("\nReached Destination, All Happies....\n");
                    return true;
                }

                // Add j into stack
                switch (addIntoStack(Stack, &WrIdx, j)) {
                    case 0:
                        printf("Already into the stack: %c\n", graph_get_node_name(j));
                        continue;
                    case 1:
                        // Added successfully
                        break;
                    case -1:
                        // Stack[] length Exceeded.
                        return false;
                    default:
                        return false;
                }
                // sleep(1);                                                            // Un-comment for slow debugging

                // Re-arrange indicators
                // it means, new element pushed into.
                // j=-1: upon next j++ in 'for' loop, it becomes 0.
                i = j;
                j = -1;
            }
        }
        // printf("WrIndx : %d\n", WrIdx);                                              // Un-comment for slow debugging

        // if WrIdx is 1, means its last element to popup.
        // once its got popup out, then src and dest are not connected.
        if (WrIdx == 1) {
            printf("Can't find route to '%c' -> '%c'\n", src, dest);
            break;
        }

        // Coudn't find destination in this
        // so popup last element and adjust j with last popup element +1.
        j = graph_get_node_index(popUpFromStack(Stack, &WrIdx))+1;

        // The WrIdx -1 will be starting search index from next.
        i = graph_get_node_index(Stack[WrIdx-1]);
    }

    return false;
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


#if 1
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
    graph_add_edge('A', 'B', TWO_WAY, 1);
    graph_add_edge('B', 'C', TWO_WAY, 2);
    graph_add_edge('E', 'D', TWO_WAY, 3);
    graph_add_edge('D', 'E', TWO_WAY, 4);
    graph_add_edge('E', 'F', TWO_WAY, 5);
    graph_add_edge('A', 'E', TWO_WAY, 6);
    graph_add_edge('C', 'E', TWO_WAY, 7);
    graph_add_edge('A', 'I', TWO_WAY, 8);
    graph_add_edge('A', 'I', TWO_WAY, 9);
    graph_add_edge('J', 'D', TWO_WAY,10);
    graph_add_edge('I', 'I', TWO_WAY,11);
    graph_add_edge('A', 'I', TWO_WAY,12);
    graph_add_edge('F', 'H', TWO_WAY,13);
    graph_add_edge('C', 'G', TWO_WAY,14);
    graph_add_edge('B', 'F', TWO_WAY,15);
    graph_add_edge('A', 'K', TWO_WAY,16);
    graph_add_edge('L', 'K', TWO_WAY,17);
    graph_add_edge('J', 'I', TWO_WAY,18);
    graph_add_edge('I', 'K', TWO_WAY,19);
#endif

    printf("\n\tInput Graph\n\n");
    graph_print();

    // Breath First Search
     bfs('A');

    // Deapth First Search
    // dfs('E', 'I');

    // Prim's Algorithm
    // prim('A');

    return;
}