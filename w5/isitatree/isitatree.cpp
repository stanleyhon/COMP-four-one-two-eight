#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cassert>


using namespace std;

int testCase = 1;

int main (void) {
    int from, to;

    set< int > knownNodes; // all known nodes
    set< int > waysTo; // the ones that have things pointing at it
    map< int, vector< int > > graph; // adjacency list, of a node and it's children.
    while (cin >> from >> to) {
        if (from == 0 && to == 0) {
            if (knownNodes.size() == 0) {
                cout << "Case " << testCase << " is a tree.\n";
                testCase++;
                continue;
            }
            bool isTree = true;
            // look through knownNodes, there will be one where there are no waysTo
            int rootId = -1;
            for (set< int >::iterator it = knownNodes.begin(); it != knownNodes.end(); ++it) {
#ifdef DEBUG
                cout << "Checking for ways to " << *it << "\n";
#endif
                if (waysTo.count(*it) == 0 && rootId == -1) {
#ifdef DEBUG
                    cout << "No ways to " << *it << "\n";
#endif
                    rootId = *it;
                } else if (waysTo.count(*it) == 0 && rootId != -1) {
#ifdef DEBUG
                    cout << " No ways to " << *it << " but already found a root. failing.\n";
#endif
                    cout << "Case " << testCase << " is not a tree.\n";
                    isTree = false;
                    break;
                }
            }

            if (isTree == true) {
#ifdef DEBUG
                cout << "Root is " << rootId << "\n";
#endif
                if (rootId == -1) {
                    cout << "Case " << testCase << " is not a tree.\n";
                    isTree = false;
                } else {
                    // do a BFS from root, make sure we see all known nodes only once each
                    set< int > bfsNodes;
                    queue< int > q;
                    q.push (rootId);
                    while (q.empty() == false) {
                        int current = q.front();
#ifdef DEBUG
                        cout << "BFS visiting " << current << "\n";
#endif
                        q.pop();
                        if (bfsNodes.count(current) != 0) {
                            // wtf we've seen this before
                            cout << "Case " << testCase << " is not a tree.\n";
                            isTree = false;
                            break;
                        } else {
                            bfsNodes.insert(current);
                        }

                        // now push on children
                        for (vector< int >::iterator it = graph[current].begin(); it != graph[current].end(); ++it) {
                            q.push (*it);
                        }
                    }

                    if (isTree == true) { // then check bfsNodes against knownNodes, they should match exactly
                        for (set< int >::iterator it = knownNodes.begin(); it != knownNodes.end(); ++it) {
                            if (bfsNodes.count (*it) != 1) {
                                cout << "Case " << testCase << " is not a tree.\n";
                                isTree = false;
                                break;
                            }
                        }
                    }

                    if (isTree == true) {
                        cout << "Case " << testCase << " is a tree.\n";
                    }
                }
            }
            // zero all the datastrcutures
            knownNodes.clear(); // all known nodes
            if (knownNodes.size() != 0) {
                assert(0);
            }
            waysTo.clear(); // the ones that have things pointing at it
            if (waysTo.size() != 0) {
                assert(0);
            }
            graph.clear(); // adjacency list, of a node and it's children.
            if (graph.size() != 0) {
                assert(0);
            }

//            cout << "finishing testcase " << testCase << "\n";
            testCase++;
        } else if (from == -1 && to == -1) {
//            cout << "We're done\n";
        } else {
#ifdef DEBUG
            cout << "From " << from << " to " << to << "\n";
#endif
            knownNodes.insert(from);
            knownNodes.insert(to);
            waysTo.insert(to);
            if (graph.count(from) == 0) {
                vector< int > v;
                v.push_back (to);
                graph[from] = v;
            } else {
                graph[from].push_back(to);
            }
        }
    }
    return 0;
}
