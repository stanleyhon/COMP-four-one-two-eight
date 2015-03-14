#include <iostream>
#include <string>
#include <utility>
#include <list>

using namespace std;

int length;

int sortedness (string s);

int main (void) {
    list< pair<int, string> > l;

    int numTestCases;
    cin >> length >> numTestCases;

    int currentCase = 0;
    list< pair<int, string> >::iterator i;
    while (currentCase < numTestCases) {
        string s;
        cin >> s;
        pair<int, string> newPair = make_pair (sortedness (s), s);
        
        // figure out where to put it
        bool inserted = false;
        for (i = l.begin(); i != l.end(); ++i) {
            if ((*i).first > newPair.first) {
                l.insert (i, newPair);
                currentCase++;
                inserted = true;
                break;
            }
        }

        // ok just put it at the end
        if (inserted == false) {
            l.push_back(newPair);
            currentCase++;
        }
    }

    for (i = l.begin(); i != l.end(); ++i) {
        cout << (*i).second << "\n";
    }

    return 0;
}

int sortedness (string s) {
    int totalUnsortedness = 0;
    int i = 0;
    while (i < length) {
        int j = i + 1;
        while (j < length) {
            if (s[i] > s[j]) {
                totalUnsortedness++;
            }
            j++;
        }
        i++;
    }
    // cout << "Sortedness of " << s << " is " << totalUnsortedness << "\n";
    return totalUnsortedness;
}
