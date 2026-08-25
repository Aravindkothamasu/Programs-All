#include"./graph.h"


////////////////        BFS         ////////////////////

// Check for all visited Nodes are not.
bool allNodesVisited(bool *visitedNode, int len) {
    int i;
    for(i=0; i < len; i++) {
        if(*(visitedNode+i)) {
            printf("%c ", graph_get_node_name(i));
        } else {
            printf("%d ", 0);
        }
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

////////////////        PRIMs         ////////////////////

int getLowerWeightIndex(int idx, bool *visitedNodeIdxPtr) {
    int i;
    // lwrWtIdx -> lower weight index, -1 is default value
    // lwrWt -> lower weight, EDGE_WEIGHT_MAX+1 is default value
    int lwrWtIdx=-1, lwrWt=EDGE_WEIGHT_MAX+1;

    // check for edge b/w idx with all nodes and get the weight and store into weights Arr
    for(i=0; i<NODES_LEN; i++) {
        // ignore if it is source
        if ( i==idx ) {
            continue;
        }

        // ignoring visited node
        if(*(visitedNodeIdxPtr+i) == true) {
           continue;
        }

        // check for edge connection b/w idx -> i
        if (graph_check_edge(graph_get_node_name(idx), graph_get_node_name(i))) {
            // store weight int the array of the connected edge
            if ( lwrWt > graph_get_weight_edge(idx, i)) {
                // store the lower wt index.
                lwrWtIdx = i;
                // update the lower weight
                lwrWt = graph_get_weight_edge(idx, i);
            }
        }
    }

    
    /*  ENABLE FOR DEBUGGING
    if( lwrWt != EDGE_WEIGHT_MAX+1 )
        printf("%s, retunning for %c - %c, weight : %d\n", __func__, graph_get_node_name(idx), graph_get_node_name(lwrWtIdx), lwrWt);
    */

    // if there is no connected edges with idx, returns -1;
    return lwrWtIdx;
}

bool prim(char src) {
    int i, idx;
    bool visitedNode[NODES_LEN] = {false};
    // Setting variables default values.
    int lwWtIdx = -1, lwWt = EDGE_WEIGHT_MAX+1;

    // Check for src graph node is present or not
    if ( -1 == graph_get_node_index(src)) {
        printf("Src '%c' is not present\n", src);
        return false;
    }

    // Marking source node index as visited.
    visitedNode[graph_get_node_index(src)] = true;

    while(true) {
        for(i=0; i<NODES_LEN; i++) {
            // ignoring non-visited nodes
            if(visitedNode[i] == false)
                continue;
            // printf("Checking now index : %c\n", graph_get_node_name(i));             // Enable for debugging

            // get the lower index edge connected to index 'i'
            idx = getLowerWeightIndex(i, visitedNode);
            if (idx == -1) {
                // Something wrong
            } else {
                // Yes, u got the lower vertex
                // printf("Yes, u got the lower edge %c <-> %c\n", graph_get_node_name(i), graph_get_node_name(idx));
                if (lwWt > graph_get_weight_edge(i, idx)) {
                    // update the latest lower weight
                    lwWt = graph_get_weight_edge(i, idx);
                    // update the later lower weight index
                    lwWtIdx = idx;
                    printf("Lower weight edges: %c <-> %c - Weight: %d\n", graph_get_node_name(i), graph_get_node_name(idx), lwWt);
                }
            }
            // sleep(1);            // enable for slow debugging
            
        }

        // reset lower weight to reset value 
        lwWt = EDGE_WEIGHT_MAX+1;

        // save the last known index
        if(-1 != lwWtIdx) {
            printf("Marking %c as visited\n", graph_get_node_name(lwWtIdx));
            // Marking lwWtIdx as visited.
            visitedNode[lwWtIdx] = true;
            // reset to default
            lwWtIdx = -1;
        }

        // Checking all nodes are visited or not, if yes, then its done
        if (allNodesVisited(visitedNode, NODES_LEN)) {
            printf("All Nodes are visited Done..... All Happiessss...\n");
            return true;
        }

        printf("\n");
    }
    return false;
}

