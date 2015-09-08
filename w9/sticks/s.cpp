#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct line {
    double xStart, yStart;
    double xEnd, yEnd;
};

#define MAX_LINES 100008
struct line lines[MAX_LINES];

double multiply (double xStart, double yStart, double xEnd, double yEnd, double xMid, double yMid) {
    return ((xStart - xMid) * (yEnd - yMid) - (xEnd - xMid) * (yStart - yMid));
}

bool intersect (struct line line1, struct line line2) {
    if (min (line1.xStart, line1.xEnd) <= max (line2.xStart, line2.xEnd) &&
        min (line1.yStart, line1.yEnd) <= max (line2.yStart, line2.yEnd) &&
        min (line2.xStart, line2.xEnd) <= max (line1.xStart, line1.xEnd) &&
        min (line2.yStart, line2.yEnd) <= max (line1.yStart, line1.yEnd) &&
        
        multiply (line2.xStart, line2.yStart, line2.xEnd, line2.yEnd, line1.xStart, line1.yStart) *
        multiply (line2.xStart, line2.yStart, line2.xEnd, line2.yEnd, line1.xEnd, line1.yEnd) <= 0 &&
        
        multiply (line1.xStart, line1.yStart, line1.xEnd, line1.yEnd, line2.xStart, line2.yStart) *
        multiply (line1.xStart, line1.yStart, line1.xEnd, line1.yEnd, line2.xEnd, line2.yEnd) <= 0) {

        return true;
    } else {
        return false;
    }
}

int main (void) {
    int numCases;
    while (scanf ("%d", &numCases) != EOF) {
        if (numCases == 0) { return 0; }

        int answerArray[MAX_LINES];
        int answerNextFree = 0;
        for (int currentLine = 1; currentLine <= numCases; currentLine++) {
            scanf ("%lf%lf%lf%lf", &lines[currentLine].xStart, &lines[currentLine].yStart, &lines[currentLine].xEnd, &lines[currentLine].yEnd);

            int position = -1;
            for (int i = 0; i < answerNextFree; i++) {
                if (answerArray[i] == -1) {
                    position = i;
                } else if (intersect (lines[currentLine], lines[answerArray[i]]) == true) {
                    answerArray[i] = -1;
                }
            }

            if (position == -1) {
                answerArray[answerNextFree++] = currentLine;
            } else {
                answerArray[position] = currentLine;
            }
        }
        sort (answerArray, answerArray + answerNextFree);
        int start = 0;
        for (; answerArray[start] == -1; start++);
        printf ("Top sticks:");
        while (start < answerNextFree) {
            printf (" %d", answerArray[start]);
            if (start == answerNextFree - 1) {
                printf (".\n");
            } else {
                printf (",");
            }
            start++;
        }
    }
    return 0;
}

