#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


using namespace std;

class edge {
  public:
    int from, to, weight;
    
    edge (int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }

    bool operator < (const edge& e1) const {
        return !(this->weight >= e1.weight);
    }

};

#define UFSIZE 205
int uf_array[UFSIZE];

void resetUF (void) {
    int i = 0;
    while (i < UFSIZE) {
        uf_array[i] = 0;
        i++;
    }
    return;
}

int find (int a) {
    int target = a;
    while (uf_array[target] != 0) {
        target = uf_array[target];
    }

    if (a != target) {
        uf_array[a] = target; // path compress
    }

    assert (uf_array[target] == 0);
    return target;
}

void un (int a, int b) {
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
    if (parentA != parentB) {
        uf_array[parentA] = parentB; 
    }
#ifdef DEBUG
    cout << "Assigning uf_array[" << a << "]" << " is " << uf_array[a] << "\n";
    cout << "Assigning uf_array[" << b << "]" << " is " << uf_array[b] << "\n";
#endif
    return;
}

void kruskals (vector< edge > * edges, int numNodes) {
#ifdef DEBUG
    cout << "Attempting kruskals\n";
#endif
    vector< edge > mst;
#ifdef DEBUG
    cout << "Before sorting the edges: \n";
    for (vector< edge >::iterator it = edges->begin(); it != edges->end(); ++it) {
        cout << it->from << " -> " << it->to << "[" << it->weight << "]\n";
    } 
#endif
    sort (edges->begin(), edges->end());
#ifdef DEBUG
    cout << "After sorting the edges: \n";
    for (vector< edge >::iterator it = edges->begin(); it != edges->end(); ++it) {
        cout << it->from << " -> " << it->to << "[" << it->weight << "]\n";
    } 
#endif
    int sum = 0;
    for (vector< edge >::iterator it = edges->begin(); it != edges->end(); ++it) {
#ifdef DEBUG
        cout << "Iterating over edges.\n";
#endif
        if (find (it->from) == find (it->to)) {
#ifdef DEBUG
            cout << "Already connected, skipping.\n";
#endif
            continue; // already connected dont bother
        } else {
            mst.push_back(*it);
            sum += it->weight;
#ifdef DEBUG
            cout << ".\n";
#endif
            un (it->from, it->to);
        }
    }

    // at this point check we can assume we have all the edges we can to form the MST.
    // check we have a complete MST:
    if (mst.size() == numNodes - 1) { // yes we do
        cout << sum << "\n";
    } else {
        cout << "-1\n";
    }
    
    // Also, get rid of the edges, we only need to keep the MST
    int mstSize = mst.size();
#ifdef DEBUG
    cout << "MST is of size " << mst.size() << " edge is of size " << edges->size() << "\n";
#endif
    edges->swap(mst);
    assert (edges->size() == mstSize);
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
        if (daysLasting < numberOfNodes - 1) { // impossible
            cout << "-1\n";
            // read daysLasting number of triplets
            int i = 0;
            while (i < daysLasting) {
                int junk, junk2, junk3;
                cin >> junk >> junk2 >> junk3;
                i++;
            }
        } else {
            int day = 0;
            while (day < daysLasting) {
                int from, to, weight;
                cin >> from >> to >> weight;
#ifdef DEBUG
                cout << "from: " << from << " to: " << to << " weight: " << weight << "\n";
#endif
                edge e (from, to, weight);
                edges.push_back (e);

                if (day >= numberOfNodes - 2) { // run kruskals and calculate MST size.
                    resetUF();
                    kruskals(&edges, numberOfNodes);
                } else {
                    cout << "-1\n";
                }
                
                day++;
            }
        }
        testCase++;
    }

    return 0;
}
