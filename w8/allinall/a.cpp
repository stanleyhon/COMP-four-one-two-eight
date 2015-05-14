#include <stdio.h>
#include <iostream>

using namespace std;

int main (void) {
    string source, other;
    while (cin >> source >> other) {
        int matchIndex = 0;
        for (int i = 0; i < other.length() && matchIndex != source.length(); i++) {
//            printf ("Comparing %c with %c\n", source[matchIndex], other[i]);
            if (source[matchIndex] == other[i]) {
                matchIndex++;
            }
        }

        if (matchIndex == source.length()) {
            printf ("Yes\n");
        } else {
            printf ("No\n");
        }
    }
    return 0;
}
