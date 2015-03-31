#include <iostream>
#include <list>
#include <queue>

#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4

#define DEBUG 1

using namespace std;

struct info {
    int f1;
    int f2;
    int distance;
    int direction;
};

queue <struct info *> inputs;

class entry {
  public:
    int ufValue;
    int x;
    int y;

    entry (int uf, int inX, int inY) {
        ufValue = uf;
        x = inX;
        y = inY;
    }
};

entry ** ufArray;

void setupUf (int numFarms) {
    ufArray = new entry*[numFarms];
    for (int i = 0; i < numFarms; ++i) {
        ufArray[i] = new entry (-1, 0, 0);
    }
    return;
}

int find (int farm1) {
#ifdef DEBUG
    cout << "finding " << farm1 << "\n";
#endif
    if (ufArray[farm1]->ufValue < 0) {
        return farm1;
    } else {
        // add our parents offset onto ourselves
        ufArray[farm1]->x += ufArray[ufArray[farm1]->ufValue]->x;
        ufArray[farm1]->y += ufArray[ufArray[farm1]->ufValue]->y;

        // path compress
        ufArray[farm1]->ufValue = find (ufArray[farm1]->ufValue);
        return ufArray[farm1]->ufValue;
    }
#ifdef DEBUG
    cout << "finished" << "\n";
#endif
}

void unify (int farm1, int farm2, int direction, int distance) {
#ifdef DEBUG
    cout << "unifying " << farm1 << " and " << farm2 <<  "\n";
#endif
    int farm1Parent = find (farm1);
    int farm2Parent = find (farm2);
    // the sizes are negative, so the MORE negative one
    // is actually the larger set
    
    // join farm2 to farm1's set
    if (ufArray[farm1Parent]->ufValue < ufArray[farm2Parent]->ufValue) {        
        ufArray[farm2Parent]->ufValue = farm1Parent;

        if (direction == NORTH) { // F1 to F2 is NORTH
            // F2's Y offset + distance
            ufArray[farm2Parent]->y += distance;
        } else if (direction == SOUTH) { // F1 to F2 is SOUTH
            // F2's Y offset - distance
            ufArray[farm2Parent]->y -= distance;
        } else if (direction == WEST) { // F1 to F2 is WEST
            // F2's X offset - distance
            ufArray[farm2Parent]->x -= distance;
        } else if (direction == EAST) { // F1 to F2 is EAST
            // F2's X offset + distance
            ufArray[farm2Parent]->x += distance;
        } else {
#ifdef DEBUG
            cout << "something went wrong A\n";
#endif
        }
    } else { // connect farm 1 to farm 2's set
        ufArray[farm1Parent]->ufValue = farm2Parent;
        if (direction == NORTH) { // F1 to F2 is NORTH
            // so F2 to F1 is SOUTH 
            // so change F1's offset value, subtract distance
            // so just flip the directionals for all these cases
            ufArray[farm1Parent]->y -= distance;
        } else if (direction == SOUTH) { // F1 to F2 is SOUTH
            ufArray[farm1Parent]->y += distance;
        } else if (direction == WEST) { // F1 to F2 is WEST
            ufArray[farm1Parent]->x += distance;
        } else if (direction == EAST) { // F1 to F2 is EAST
            ufArray[farm1Parent]->x -= distance;
        } else {
#ifdef DEBUG
            cout << "something went wrong B\n";
#endif
        }
    }
    return;
}

struct request {
    int from;
    int to;
};

struct request * requests[10000];

class Mycomparison {
    public:
    bool operator() (pair<int, int> p1, pair<int, int> p2) {
        return (p1.first > p2.first); // TODO: not sure if this is right
    }
};

priority_queue<pair<int, int>, vector<pair<int, int> >, Mycomparison> request_ordering;

int answers[10000];

int main (void) {

    // n is num farms
    // m is num queries.
    int n, m;
    cin >> n >> m;
    int currentLine = 1;
    while (currentLine < m) {
        int f1, f2, length;
        char direction;
        cin >> f1 >> f2 >> length >> direction;
        int numericalDirection = -1;
        if (direction == 'N') {
            numericalDirection = NORTH;
        } else if (direction == 'S') {
            numericalDirection = SOUTH;
        } else if (direction == 'W') {
            numericalDirection = WEST;
        } else if (direction == 'E') {
            numericalDirection = EAST;
        }
        struct info * newInfo = new info;
        newInfo->f1 = f1;
        newInfo->f2 = f2;
        newInfo->distance = length;
        newInfo->direction = numericalDirection; 
        inputs.push (newInfo);
        ++currentLine;
    }

    int numQueries;
    cin >> numQueries;
    currentLine = 0;
    int uid = 0;
    while (currentLine < numQueries) {
        int from, to, timeIndex;
        cin >> from >> to >> timeIndex;
        request_ordering.push (make_pair (timeIndex, uid));
        requests[uid] = new request;
        requests[uid]->from = from;
        requests[uid]->to = to;
        uid++;
        currentLine++;
    }

    // now do work
    int currentTime = 0;
    while (request_ordering.empty() == false) {
        pair<int, int> currentJob = request_ordering.top();
        request_ordering.pop();
        while (currentTime < currentJob.first) {
            // need to forward time a bit
            struct info * next = inputs.front();
            inputs.pop();
            unify (next->f1, next->f2, next->direction, next->distance);
            currentTime++;
        }

        if (currentTime >= currentJob.first) { // thats fine we can answer the query now.
            int from, to;
            from = requests[currentJob.second]->from;
            to = requests[currentJob.second]->to;
            int fromParent = find (from);
            int toParent = find (to);

            if (fromParent != toParent) { // we can't answer this
                answers[uid] = -1;
            } else {
                int xDistance = ufArray[from]->x - ufArray[to]->x;
                if (xDistance < 0) {
                    xDistance = xDistance * -1;
                }
                int yDistance = ufArray[from]->y - ufArray[to]->y;
                if (yDistance < 0) {
                    yDistance = yDistance * -1;
                }
                answers[uid] = xDistance + yDistance;
            }
        } else {
#ifdef DEBUG
            cout << "something went wrong C\n";
#endif
            //wtf
        }
    }

    for (int i = 0; i < uid; ++i) {
        cout << answers[i] << "\n";
    }

    return 0;
}
            
             

        




