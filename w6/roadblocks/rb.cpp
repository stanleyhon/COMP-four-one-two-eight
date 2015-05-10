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

vector < int > dist [MAX_NODES];

int runD (void) {
    priority_queue < nextPair, vector < nextPair >, greater < nextPair > > pq;
    // start with a pair of COST 0, LOCATION 0
    pq.push (make_pair (0, 1));
    
    while (pq.empty() == false) {
        pair<int, int> next = pq.top();
        pq.pop();
        int cost = next.first;
        int destination = next.second;
        if (dist[destination].size() == 2) {
            continue;
        }

        if (dist[destination].empty() || dist[destination][0] < cost) {
            dist[destination].push_back(cost);
            if (destination == nodes && dist[destination].size() == 2) return cost;
            for (int i = 0; i < edgeArray[destination].size(); ++i) {
                edge e = edgeArray[destination][i];
                if (dist[e.to].size() < 2) {
                    pq.push (make_pair (cost + e.weight, e.to));
                }
            }
        }
    }
    // at this point, best should have shortest path
    // secondBest should have second best path
    printf ("%d\n", secondBest[nodes]);

    return -1;
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

    printf ("%d\n", runD ());

    return 0;
}
