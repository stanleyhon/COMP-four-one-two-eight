#include <iostream>
#include <list>
#include <set>

using namespace std;

void find (int queryA, int queryB);

class node {
    public:
        int name;
        node * parent;

        node (int newName) {
            parent = NULL;
            name = newName;
        }

        void attachChild (node * child) {
            child->parent = this;
            // cout << "attaching " << this->name << " to " << child->name << "\n";
        }
};

node* nodeList[10001];

int main (void) {
    int testCases;
    cin >> testCases;

    int current = 0;
    while (current < testCases) {
        int numNodes;
        cin >> numNodes;

        int freeCount = 1;
        if (nodeList[1] != NULL) {
            while (freeCount < 10002) {
                if (nodeList[freeCount] != NULL) {
                    delete nodeList[freeCount];
                    nodeList[freeCount] = NULL;
                }
                freeCount++;
            }
        }

        int count = 1;
        while (count <= numNodes) {
            nodeList[count] = new node (count);
            count++;
        }

        int currentRead = 0;
        while (currentRead < numNodes - 1) {
            int parent, child;
            cin >> parent >> child;

            nodeList[parent]->attachChild (nodeList[child]);
            currentRead++;
        }

        int queryA, queryB;
        cin >> queryA >> queryB;

        // find common ancestor
        find (queryA, queryB);

        current++;
    }

    cout << "\n";
    return 0;
}

void find (int queryA, int queryB) {
    node * a = nodeList[queryA];
    node * b = nodeList[queryB];

    set<int> parentsOfA;
    while (a != NULL) {
        parentsOfA.insert(a->name);
        a = a->parent;
    }

    while (b != NULL) {
        if (parentsOfA.count (b->name) != 0) {
            cout << b->name << "\n";
            return;
        }
        b = b->parent;
    }
    return;
}
