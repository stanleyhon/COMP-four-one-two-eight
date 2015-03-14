#include <iostream>
#include <string>
#include <list>
#include <sstream>
using namespace std;

int layer[20][20];
int temp[20][20];

string* printIt (int gridSize);
void iterateSlice (int fuel);
void go (int fuel);

int main (void) {
    int i = 0;
    while (i < 20) {
        int j = 0;
        while (j < 20) {
            temp[i][j] = -1;
            j++;
        }
        i++;
    }
    
    int scenarios;
    cin >> scenarios;
    int currentScenario = 1;
    while (currentScenario <= scenarios) {
        cout << "Scenario #" << currentScenario << ":\n";
        int fuel;
        cin >> fuel;

        if (fuel == 0) {
            cout << "slice #1:\n0\n";
        } else {
            go (fuel);
        }

        cout << "\n";
        currentScenario++;
    }

    return 0;
}

void go (int fuel) {
    // calculate grid size first
    int gridSize = 1 + (2 * fuel);
    
    int slice = 1;
    // initialise to -1
    int i = 0;
    while (i < 20) {
        int j = 0;
        while (j < 20) {
            layer[i][j] = -1;
            j++;
        }
        i++;
    }

    // remember the slices to reprint them later
    list<string*> sliceList;
    // Place the root 
    layer[fuel][fuel] = fuel;

    while (slice <= fuel + 1) {
        cout << "slice #" << slice << ":\n";
        // print slice
        string * s = printIt(gridSize);
        cout << *s;

        sliceList.push_front(s);

        // iterate slice
        iterateSlice (fuel);

        slice++;
    }

    // pop one off.
    sliceList.pop_front();

    list<string*>::iterator it;
    for (it = sliceList.begin(); it != sliceList.end(); ++it) {
        cout << "slice #" << slice << ":\n";
        slice++;
        cout << *(*it);
    }

    return;
}

void iterateSlice (int fuel) {
    int row = 0;
    int gridSize = (1 + (2 * fuel));
    while (row <  gridSize) {
        int col = 0;
        while (col < gridSize) {
            if (layer[row][col] == fuel) { // need expand
                // try up
                if (row - 1 >= 0 && layer[row-1][col] == -1) {
                    temp[row-1][col] = fuel;
                }

                // try down
                if (row + 1 < gridSize && layer[row+1][col] == -1) {
                    temp[row+1][col] = fuel;
                }

                // try left
                if (col - 1 >= 0 && layer[row][col-1] == -1) {
                    temp[row][col-1] = fuel;
                }

                // try right
                if (col + 1 < gridSize && layer[row][col+1] == -1) {
                    temp[row][col+1] = fuel;
                }
            }                
            // once expanded, it should be reduced by 1
            // alternatively, if we run into anything on the board
            // it should stil go down by 1 on an expand
            if (layer[row][col] != -1) {
                temp[row][col] = layer[row][col] - 1;
            }
            col++;
        }
        row++;
    }

    // copy temp into layer
    int i = 0;
    while (i < gridSize) {
        int j = 0;
        while (j < gridSize) {
            layer[i][j] = temp[i][j];
            j++;
        }
        i++;
    }

    // clear temp
    i = 0;
    while (i < 20) {
        int j = 0;
        while (j < 20) {
            temp[i][j] = -1;
            j++;
        }
        i++;
    }

    return;
}

string* printIt (int gridSize) {
    string * s = new string();
    int row = 0;
    while (row < gridSize) {
        int col = 0;
        while (col < gridSize) {
            if (layer[row][col] == -1) {
                s->append(".");
            } else {
                ostringstream convert;
                convert << layer[row][col];
                s->append(convert.str());
            }
            col++;
        }
        s->append("\n");
        row++;
    }
    return s;
}
