// BF join all points in AM
// then fuckin dijkstras yo 
#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <map>
#include <cmath>
#include <stdio.h>

// #define DEBUG 1

using namespace std;

// Map from STONE NUM -> PAIR ( X, Y )
int numStones;
map < int, pair < int , int > > stones;
double am[205][205];

void init (void) {
    for (int i = 0; i < 205; i++) {
        for (int j = 0; j < 205; j++) {
            am[i][j] = -1;
        }
    }
    
    stones.clear();
    return;
}

#define INFYO 2000

double dijkstra (void) {
    bool visited[205];
    double cost[205];
    for (int i = 0; i < 205; i++) {

        // in theory max distnce is < 2000
        cost[i] = INFYO;
        visited[i] = false;
    }
    cost[1] = 0;
    double answer = 0;

    for (int i = 0; i < numStones; i++) {
#ifdef DEBUG
        printf ("Iteration %d\n", i);
#endif
        int currentNode = -1;
        double longestSoFar = INFYO;
        for (int target = 1; target <= numStones; ++target) {
            if (visited[target] == false && cost[target] <= longestSoFar) {
                longestSoFar = cost[target];
                currentNode = target;
            }
        }
#ifdef DEBUG
        printf ("currentNode is %d\n", currentNode);
#endif

        visited[currentNode] = true;
        // at this point, currentNode, should have the guy we want to update some costs for
        if (cost[currentNode] > answer && cost[currentNode] != INFYO) {
            answer = cost[currentNode];
        }

        // if we've already done 2, then we're finished
        if (currentNode == 2) {
            return answer;
        }

        for (int count = 1; count <= numStones; ++count) {
            // cost is either, direct cost, or the cost in the adjaceny matrix
            if (visited[count] == false) {
                if (cost[count] > am[currentNode][count]) {
                    cost[count] = am[currentNode][count];
                }
            }
        }
    }
    assert (false);
    return -1;
}


int main (void) {
    int scenarioNumber = 1;
    scanf ("%d", &numStones);
    while (numStones != 0) {
        // clear AM
        init();

        int stoneNumber = 1;
        while (stoneNumber <= numStones) {
            int x, y;
            scanf ("%d %d", &x, &y);

            stones[stoneNumber] = make_pair (x, y);

            // add an edge between this guy, and all previous guys
            for (int i = stoneNumber - 1; i >= 1; --i) {
                double ix = stones[i].first;
                double iy = stones[i].second;
                double xDist = ix - x;
                double yDist = iy - y;
                double distanceToUs = xDist*xDist + yDist*yDist;
                distanceToUs = sqrt (distanceToUs);
            
                // add an edge between i and stonenumber with cost distanceToUs
                am[i][stoneNumber] = distanceToUs;
                am[stoneNumber][i] = distanceToUs;
            }
            
            stoneNumber++;
        }

        // now run dijkstra's
        double answer = dijkstra ();
        printf ("Scenario #%d\nFrog Distance = %.3f\n\n", scenarioNumber++, answer);
        scanf ("%d", &numStones);
    }

    return EXIT_SUCCESS;
}

