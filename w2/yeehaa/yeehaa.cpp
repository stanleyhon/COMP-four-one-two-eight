#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

void domath (double radius, int bullets) {
    double pi = 3.141592653589793238462; 
    double radians = 2 * pi;
    radians = radians / bullets;
    radians = radians / 2;
    double littleR = (radius * sin (radians)) / (1 + sin (radians));
    printf ("%.3f\n\n", littleR);
    return;
}

int main (void) {
    int testCases;
    cin >> testCases;
    int currentCase = 1;
    while (currentCase <= testCases) {
        double radius;
        int bullets;
        cin >> radius >> bullets;

        cout << "Scenario #" << currentCase << ":\n";
        domath (radius, bullets);
        currentCase++;
    }
    return 0;
}

