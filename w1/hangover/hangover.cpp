#include <iostream>

using namespace std;

int main (void) {
    double input;
    double total = 0;
    double cards = 1;
    
    cin >> input;
    while (input != 0) {
        total = total + (1 / (cards + 1));
        if (total >= input) { // ok we've achieved the overhang
            cout << cards << " card(s)\n";
            cin >> input;
            cards = 1;
            total = 0;
        } else {
            cards++;
        }
    }

    return 0;
}
