#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int caseNum = 1;

vector< int > * al;
map< int, int > * waysTo;
set< int > * seen;
void isTree (void) {
    if (seen->size() == 0) {
        cout << "Case " << caseNum << "is a tree.\n";
        caseNum++;
        return;
    }
    bool isTree = true;
    // verify waysTo is all 1 except 1
    bool rootSeen = false;
    int rootId = -1;
    // Check that everything only has been linked TO once, except root.
    for (map< int, int >::iterator it = waysTo->begin(); it != waysTo->end(); ++it) {
        if (it->second != 1 && rootSeen == false) {
            rootSeen = true;
            rootId = it->first;
        } else if (it->second != 1 && rootSeen == true) {
            cout << "Case " << caseNum << "is not a tree.\n";
            caseNum++;
            return;
        }
    }

    // Now start from AL and do a traversal, we should pass everything we've seen only once.
    queue< int > q;
    set< int > traverseSeen;
    q.push (rootId);
    while (q.empty() == false) {
        int current = q.front();
        if (traverseSeen.count(current) == 0) {
            traverseSeen.insert(rootId);
        } else {
            cout << "Case " << caseNum << "is not a tree.\n";
            caseNum++;
            return;
        }
        q.pop();

        for (vector< int >::iterator it = al[current].begin(); it != al[current].end(); ++it) {
            q.push (*it);
        }
    }

    // Now check our traverseSeen is the same as global seen
    if (traverseSeen != (*seen)) {
        cout << "Case " << caseNum << "is not a tree.\n";
    } else {
        cout << "Case " << caseNum << "is a tree.\n";
    }
    caseNum++;
    return;

}

int main (void) {
    seen = new set< int >();
    al = new vector< int >[1000]();
    waysTo = new map< int, int >();
    int from, to;
    while (cin >> from >> to && from != -1 && to != -1) {
        if (from == 0 && to == 0) {
            // is it a tree?
            isTree ();

            al = new vector< int >[1000]();
            waysTo = new map< int, int >();
            seen = new set< int >();
        } else {
            seen->insert(from);
            seen->insert(to);
            al[from].push_back(to);
            (*waysTo)[to]++;
        }

    }
    return 0;
}
