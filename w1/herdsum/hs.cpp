#include <iostream>

using namespace std;

int main (void) {

    int i = 0;
    cin >> i;
    
    int start = 1;
    int progress = 2;
    int end = i;

    int howMany = 0;

    int currentSum = 1;
    while ((start <= end) && (progress <= end + 1)) {
        if (currentSum < end) {
            // add one more
            currentSum += progress;
            progress++;
        } else if (currentSum > end) {
            // take the last one off
            currentSum -= start;
            start++;
        } else if (currentSum == end) {
            // we found one!
            currentSum += progress;
            // cout << start << ":" << progress-1 << endl;
            progress++;
            howMany++;
        }
    }

    cout << howMany;

    return 0;
}
