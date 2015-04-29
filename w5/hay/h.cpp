#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <queue>

// #define DEBUG 1
using namespace std;

int am[2005][2005];

//                      WEIGHT       LOCATION
typedef pair < int, int > PAIR;
priority_queue < PAIR, vector < PAIR >, greater < PAIR > > pq;

int numNodes, numRoads;

int prims (void) {
    int mostCostly = 0;
    bool visitedNodes[2005];
    for (int i = 0; i < 2005; ++i) {
        visitedNodes[i] = false;
    }

    int visitedCount = 0;
    pq.push (make_pair (0, 1));
    while (pq.empty() == false) {
        if (visitedCount == numNodes) {
            break;
        }
        pair < int, int > current = pq.top();
        pq.pop();
        int location = current.second;
        int cost = current.first;
#ifdef DEBUG
        printf ("Headed to %d costing %d\n", location, cost);
#endif 

        // have we been here before?
        if (visitedNodes[location] == true) {
            continue;
        } else { // no we have not. so go there and take into account it's cost.
            visitedNodes[location] = true;
            visitedCount++;
            if (mostCostly < cost) {
                mostCostly = cost;
            }
            
            // now, look at all places that guy can lead to
            // add them all onto the queue
            for (int i = 0; i <= numNodes; ++i) {
                if (visitedNodes[i] == true) {
#ifdef DEBUG
                    printf ("Already visited node %d, Skipping this edge\n", i);
#endif 
                    continue;
                } else if (am[location][i] != -1) { // we can, so add it
                    pq.push (make_pair (am[location][i], i));
#ifdef DEBUG
                    printf ("Haven't seen %d before, pushing on with cost %d\n", i, am[location][i]);
#endif 
                }
            }
        }
    }
    return mostCostly;
}

int main (void) {
    for (int i = 0; i < 2005; ++i) {
        memset (am[i], -1, sizeof(int)*2005);
    }

    assert (am[512][512] == -1);

    scanf ("%d %d", &numNodes, &numRoads);
#ifdef DEBUG
    printf ("NumNodes: %d numRoads: %d\n", numNodes, numRoads);
#endif
    for (int i = 0; i < numRoads; ++i) {
        int from, to, weight;
        scanf ("%d %d %d", &from, &to, &weight);

        // Why would we ever consider a longer road over a shorter one?
        if (am[from][to] > weight || am[from][to] == -1) {
            am[from][to] = weight;
            am[to][from] = weight;
        }

    }
    
    int result = prims();
    printf ("%d\n", result);

    return EXIT_SUCCESS;
}



