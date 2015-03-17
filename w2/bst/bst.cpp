#include <iostream>
#include <cmath>

#define LEFT 0
#define RIGHT 1


using namespace std;

int goDown (unsigned level, unsigned int current, unsigned int direction) {
    unsigned int step = pow (2, level-1); // WARNING DIRTY HACK <-----------
    if (direction == LEFT) {
        return (current - step);
    } else {
       return (current + step);
    } 
}

int getLevel (unsigned int target) {
    // We go up the left column until we reach or pass our target
    unsigned int current = 1;
    int level = 0;
    while (current < target) {
        current = current + (pow (2, level));
        level++;
    }
#ifdef DEBUG
    cout << "Found first larger than our target, " << current << "\n";
#endif
    // navigate left and right until we reach our target.
    while (current != target) {
        if (current > target) {
            // go left
            current = goDown (level, current, LEFT);
            level--;
        } else {
            // go right
            current = goDown (level, current, RIGHT);
            level--;
        }
    }
#ifdef DEBUG
    cout << "getLevel returning level " << level << "\n";
#endif

    return level;
}

int main (void) {
    int testCases;
    cin >> testCases;
    int count = 0;
    while (count < testCases) {
        int root;
        cin >> root;
        int level = getLevel (root);
        
        int leftLevel = level;
        int leftRoot = root;
        while (leftLevel > 0) {
            leftRoot = goDown (leftLevel--, leftRoot, LEFT);
#ifdef DEBUG
            cout << "going left, currently " << leftRoot << "\n";
#endif
        }
        cout << leftRoot << " ";

        int rightLevel = level;
        int rightRoot = root;
        while (rightLevel > 0) {
            rightRoot = goDown (rightLevel--, rightRoot, RIGHT);
        }
        cout << rightRoot << "\n";
        count++;
    }
    return 0;
}
