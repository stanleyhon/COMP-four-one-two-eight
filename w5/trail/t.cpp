#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>

// #define DEBUG 1
using namespace std;

struct edge_ {
    int from, to, weight;
};

typedef struct edge_ edge;

bool cmp (edge a, edge b) {
    return a.weight < b.weight;
}

#define UFSIZE 205
int uf_array[UFSIZE];
int num_edges;
edge edge_array[6005];
edge mst[6005];

inline int find (int a) {
    int target = a;
    while (uf_array[target] != 0) {
        target = uf_array[target];
    }

    return target;
}

inline void un (int a, int b) {
#ifdef DEBUG
    cout << "finding parentB\n";
#endif
    int parentB = find (b);
#ifdef DEBUG
    cout << "finding parentA\n";
#endif
    int parentA = find (a);
#ifdef DEBUG
    cout << "Assigning\n";
#endif
    uf_array[parentA] = parentB; 
#ifdef DEBUG
    cout << "Assigning uf_array[" << a << "]" << " is " << uf_array[a] << "\n";
    cout << "Assigning uf_array[" << b << "]" << " is " << uf_array[b] << "\n";
#endif
    return;
}

inline void kruskals (int numNodes) {
    int mst_size = 0;
#ifdef DEBUG
    cout << "Attempting kruskals\n";
#endif
    
    sort (edge_array, edge_array + num_edges, cmp); 
    int sum = 0;
#ifdef DEBUG
     cout << "Starting look at sorted edges, Number of edges is: " << num_edges << "\n";
#endif
    for (int idx = 0; idx < num_edges; ++idx) {
#ifdef DEBUG
        cout << "Iterating over edges.\n";
#endif
        if (find (edge_array[idx].from) == find(edge_array[idx].to)) {
#ifdef DEBUG
            cout << "Already connected, skipping.\n";
#endif
            continue; // already connected dont bother
        } else {
#ifdef DEBUG
            cout << "MST " << mst_size << "add " << edge_array[idx].from << " to " << edge_array[idx].to << " of weight " << edge_array[idx].weight << "\n";
#endif
            mst[mst_size] = edge_array[idx];
            mst_size++;
#ifdef DEBUG
            cout << "MST " << mst_size << " new MST_SIZE\n";
#endif
            sum += edge_array[idx].weight;
            un (edge_array[idx].from, edge_array[idx].to);
        }
    }

    // at this point check we can assume we have all the edges we can to form the MST.
    // check we have a complete MST:
    if (mst_size == numNodes - 1) { // yes we do
        // Also, get rid of the edges, we only need to keep the MST

        for (int idx = 0; idx < mst_size; ++idx) {
#ifdef DEBUG
            cout << "MST copying " << mst[idx].from << "->" << mst[idx].to << "[" << mst[idx].weight << "]\n";
#endif
            edge_array[idx] = mst[idx];
        }
#ifdef DEBUG
        cout << "Updating num_edges to " << mst_size << "\n"; 
#endif
        num_edges = mst_size;
        cout << sum << "\n";
    } else {
        cout << "-1\n";
    }
    
    return;
}

int main (void) {
    /*
    assert (find(5) == 5);
    assert (find (100) == 100);
    un (1, 2);
    assert (find(1) == find(2));
    un (1, 15);
    assert (find(1) == find(2));
    assert (find(1) == find(15));
    assert (find(1) != find(3));
*/
    int testCases;
    cin >> testCases;
    int testCase = 1;
    while (testCase <= testCases) {
        vector< edge > edges;

        cout << "Case " << testCase << ":\n";
        int numberOfNodes, daysLasting;
        cin >> numberOfNodes >> daysLasting;
        int day = 0;
        while (day < daysLasting) {
            int from, to, weight;
            scanf ("%d %d %d", &from, &to, &weight);
#ifdef DEBUG
            cout << "storing into " << num_edges << " from: " << from << " to: " << to << " weight: " << weight << "\n";
#endif
            edge_array[num_edges].from = from;
            edge_array[num_edges].to = to;
            edge_array[num_edges].weight = weight;
            num_edges++;

            memset (uf_array, 0, sizeof(int) * UFSIZE);
            kruskals(numberOfNodes);
            
            day++;
        }
        num_edges = 0;
        testCase++;
    }

    return 0;
}
