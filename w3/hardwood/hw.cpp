#include <map>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main (void) {
    string s;
    double total = 0;
    map <string,int> m;
    while (getline (cin, s)) {
        total++;
        if (m.count(s) > 0) {
            m[s]++;
        } else {
            m[s] = 1;
        }
    }

    for (map<string,int>::iterator i = m.begin(); i != m.end(); ++i) {
        cout << i->first;
        printf (" %.4f\n", (i->second / total) * 100);
    }

    return 0;
}


