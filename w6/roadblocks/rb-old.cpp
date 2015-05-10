#include <stdio.h>
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

// read in all the shit
// do dijkstra twice, at the same time
// use two values per node
// one keeps track of the best we've seen
// update the second one whenever we update the best we've seen to keep track of 2nd best.

using namespace std;

#define MAX_NODES 5005
#define MAX_ROADS 100005

int best[MAX_NODES];
int secondBest[MAX_NODES];

typedef struct edge {
    int from, to, weight;
} edge;

vector < edge > edgeArray[MAX_ROADS];

#define INF 100000
int roads = -1;
int nodes = -1;

typedef pair < int, int > nextPair;

void runD (void) {
    // initialise best and secondBest
    for (int i = 0; i < MAX_NODES; i++) {
        best[i] = INF;
        secondBest[i] = INF;
    };

    // free to start.
    best[0] = 0;

    priority_queue < nextPair, vector < nextPair >, greater < nextPair > > pq;
    // start with a pair of COST 0, LOCATION 0
    pq.push (make_pair (0, 1));
    
    while (pq.empty() == false) {
        nextPair n = pq.top();
        pq.pop();
        int cost = n.first;
        int location = n.second;

        // is going here any good?
        if (cost > secondBest[location]) { // nope... don't bother, it's worse than our worst.
            continue;
        }
        // iterate over the edges then
        for (int i = 0; i < edgeArray[location].size(); ++i) {
            edge e = edgeArray[location][i];
            int destination = e.to;
            int sumCost = cost + e.weight;

            if (best[destination] != INF || secondBest[destination] != INF) {

                // OK not bad. Lets see if it's better than our best.
                if (sumCost < best[destination]) {
                    int oldBest = -1;
                    // OK, it's way good.
                    oldBest = best[destination];
                    best[destination] = sumCost;
                    pq.push (make_pair (sumCost, destination)); // now we need to see if its a better way to get there

                    // Replace second best too and do dijkstras there
                    secondBest[destination] = oldBest;
                    pq.push (make_pair (oldBest, destination));

                } else { // its not better than best
                    // Is it better than second best?
                    if (sumCost < secondBest[destination] && sumCost > best[destination]) {
                        secondBest[destination] = sumCost;
                        pq.push (make_pair (sumCost, destination));
                    }
                }
            }
        }
    }
    // at this point, best should have shortest path
    // secondBest should have second best path
    printf ("%d\n", secondBest[nodes]);

    return;
}

int main (void) {
    scanf ("%d %d", &nodes, &roads);
    assert (roads != -1 && nodes != -1);

    edge e;
    while (scanf ("%d %d %d", &(e.from), &(e.to), &(e.weight)) == 3) {
//         printf ("Read %d %d %d\n", e.from, e.to, e.weight);
        edgeArray[e.from].push_back (e);
        int temp = e.from;
        e.from = e.to;
        e.to = temp;
        edgeArray[e.from].push_back (e);
    }

    runD ();

    return 0;
}
