#include <iostream>

using namespace std;

#define JOHN_COW 1
#define BOB_COW 2
#define BLANK 3

#define VIABLE 5
#define NOT_VIABLE 6

int field[100][100];
int size;

void debugShowGraph (void);
int viable (int xCandidate, int yCandidate, bool * blankUsed);

int main (void) {
    cin >> size;

    int y = size - 1;
    while (y >= 0) {
        int x = 0;
        while (x < size) {
            char c;
            cin >> c;
            if (c == 'J') {
                field[x][y] = JOHN_COW;
            } else if (c == 'B') {
                field[x][y] = BOB_COW;
            } else if (c == '*') {
                field[x][y] = BLANK;
            } else {
                continue;
            }
            x++;
        }
        y--;
    }

    debugShowGraph();

    double largestSideSoFar = 0;
    y = size - 1;
    while (y >= 0) {
        int x = 0;
        while (x < size) {
            //cout << "Checking " << x << ":" << y << "\n";
            if (field[x][y] == JOHN_COW) { // Lets try find a pair
                //cout << "potential root\n";
                int innerY = y; // only consider pairs lower or equal than us in Y, as to reduce dupes
                while (innerY >= 0) {
                    int innerX = 0;
                    while (innerX < size) {
                        // try and pair
                        if (field[innerX][innerY] != BOB_COW &&
                            (innerX != x || innerY != y)) {
                            // potential pair, lets see how great a square would be before we try
                            // (x1 - x2)^2 + (y1 - y2)^2 gives us the square's side length squared
                            // hence the area.
                            double area = (x - innerX)*(x - innerX) + (y - innerY)*(y - innerY);
                            if (area <= largestSideSoFar) {
                                innerX++;
                                //cout << "Skipping because smaller\n";
                                continue;
                            } else {
                                //cout << "New Pair: (" << innerX << ":" << innerY << ")\n";
                                //cout << "ROOT: (" << x << ":" << y << ")\n";
                                // validate.
                                // There are 2 candidate sets we need to consider.

                                int xDiff = x - innerX;
                                int yDiff = y - innerY;
                                // Their coordinates are as follows:
                                // Set 1: (x + yDiff, y - xDiff) & (innerX + yDiff, innerY - xDiff)
                                // Set 2: (innerX - yDiff, innerY + xDiff) & (x - yDiff, y + xDiff)
                                
                                // If innerX,innerY is already blank, we've already used our extra cow
                                bool blankUsed = false;
                                if (field[innerX][innerY] == BLANK) {
                                    blankUsed = true;
                                }

                                double xCandidate1 = x + yDiff;
                                double yCandidate1 = y - xDiff;
                                double xCandidate2 = innerX + yDiff;
                                double yCandidate2 = innerY - xDiff;

                                //cout << "Testing candidate pairs: " << xCandidate1 << ":" << yCandidate1 << " AND " << xCandidate2 << ":" << yCandidate2 << "\n";
                                if (xCandidate1 >= 0 && yCandidate1 < size && xCandidate2 >= 0 && yCandidate2 < size) {
                                    if (viable (xCandidate1, yCandidate1, &blankUsed) == VIABLE &&
                                        viable (xCandidate2, yCandidate2, &blankUsed) == VIABLE) {
                                        // update largest
                                        //cout << "Success.\n";
                                        largestSideSoFar = area;
                                        innerX++;
                                        continue;
                                    }
                                }
                                //cout << "Failure.\n";
                                // reset blankUsed
                                // If innerX,innerY is already blank, we've already used our extra cow
                                blankUsed = false;
                                if (field[innerX][innerY] == BLANK) {
                                    blankUsed = true;
                                }
           
                                double xCandidate3 = innerX - yDiff;
                                double yCandidate3 = innerY + xDiff;
                                double xCandidate4 = x - yDiff;
                                double yCandidate4 = y + xDiff;
                                
                                //cout << "Testing candidate pairs: " << xCandidate3 << ":" << yCandidate3 << " AND " << xCandidate4 << ":" << yCandidate4 << "\n";
                                if (xCandidate3 >= 0 && yCandidate3 < size && xCandidate4 >= 0 && yCandidate4 < size) {
                                    if (viable (xCandidate3, yCandidate3, &blankUsed) == VIABLE &&
                                        viable (xCandidate4, yCandidate4, &blankUsed) == VIABLE) {
                                        // update largest
                                        largestSideSoFar = area;
                                        //cout << "Success.\n";
                                    }
                                }
                                //cout << "Failure.\n";
                            }
                        }
                        innerX++;
                    }
                    innerY--;
                }
            }
            x++;
        }
        y--;
    }

    cout << largestSideSoFar;
    return 0;
}

int viable (int xCandidate, int yCandidate, bool * blankUsed) {
    if ((xCandidate >= 0 && yCandidate < size) &&
        (xCandidate < size && yCandidate >= 0)) {
        int val = field[xCandidate][yCandidate];
        if (val == JOHN_COW) {
            return VIABLE;
        } else if (val == BLANK) {
            if ((*blankUsed) == false) {
                (*blankUsed) = true;
                return VIABLE;
            } else {
                return NOT_VIABLE;
            }
        } else {
            return NOT_VIABLE;
        }
    }
    return NOT_VIABLE;
}

void debugShowGraph (void) {
    int row = size - 1;
    while (row >= 0) {
        int col = 0;
        while (col < size) {
            if (field[col][row] == BOB_COW) {
                //cout << "B";
            } else if (field[col][row] == JOHN_COW) {
                //cout << "J";
            } else if (field[col][row] == BLANK) {
                //cout << "*";
            } else {
                //cout << field[col][row];
            }
            col++;
        }
        //cout << "\n";
        row--;
    }
    return;
}
