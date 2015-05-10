#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_NODES 150*2
#define B_NODE_START 150

#define SOURCE 0
#define SINK 149
int bp[MAX_NODES][MAX_NODES];

long long flow;
bool vis[MAX_NODES];

bool dfs (int from) {
    // look at all of from's children
    for (int i = 1; i < MAX_NODES; i++) {
        if (bp[from][i] == 1 && vis[i] == false) { // Try going down there.

            //if (from < B_NODE_START) {
            //    printf ("Travelling from %d ->", from);
            //} else {
            //    printf ("Travelling from %d ->", from - B_NODE_START);
            //}

            //if (i >= B_NODE_START) {
            //    printf (" %d\n", i - B_NODE_START);
            //} else {
            //    printf (" %d\n", i);
            //}

            vis[i] = true;
            
            if (i == SINK) {
                // printf ("SINK from [%d][%d] -> %d.\n", from, from - B_NODE_START, SINK);
                bp[from][SINK] = 0;
                bp[SINK][from] = 1;
                // printf ("Found a path!\n");
                return true; 
            } else if (dfs (i) == true) {
                // found a way to the end, increment flow
                // reverse this link and return true
                bp[from][i] = 0;
                bp[i][from] = 1;
                return true;
            }
        }
    }
    return false;
}

int main (void) {
    int testcases;
    scanf ("%d", &testcases);
    while (testcases--) {

        flow = 0;
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                bp[i][j] = 0;
            }
        }

        long long intersections, streets;
        scanf ("%lld %lld", &intersections, &streets);
        while (streets--) {
            int from, to;
            scanf ("%d %d", &from, &to);

            bp[from][B_NODE_START+to] = 1;
            bp[SOURCE][from] = 1;
            bp[B_NODE_START+to][SINK] = 1;
        }
    
        for (int i = 0; i < MAX_NODES; i++) {
            vis[i] = false;
        }
        while (dfs(SOURCE) == true) {
            flow++;
            for (int i = 0; i < MAX_NODES; i++) {
                vis[i] = false;
            }
        } 

        printf ("%lld\n", intersections - flow);
    }
    return 0;
}
