#include <iostream>

using namespace std;

int array[100][100];
int dp[100][100];

int totalRows;
void dpGo (int row, int col);

int main(int argc, char **argv)
{
    for (int i = 0; i != 100; ++i) {
        for (int j = 0; j != 100; ++j) {
            array[i][j] = -1;
            dp[i][j] = -1;
        }
    }

    cin >> totalRows;
    
    int input;
    int currentRow = 0;
    int currentColumn = 0;
    while (cin >> input) {
//        cout << "READ " << input << "\n";
//        cout << "WRITE " << currentColumn << " " << currentRow << "\n";
        array[currentColumn][currentRow] = input;
        currentColumn++;
        // row 0 reads 1 things, row 3 reads 4 things
        if (currentColumn > currentRow) {
            // we've already done "currentColumn" things.
            // go up a row
            currentRow++;
            currentColumn = 0;
        }
    }
   
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            cout << array[i][j] << " ";
//        }
//        cout << "\n";
//    }

    dpGo(0,0);
    cout << dp[0][0]; 
    
    return 0;
}

void dpGo (int row, int col) {
    if (dp[col][row] == -1) {
        if (row == totalRows - 1) {
            // cout << "found a bottom one, just putting ourselves " << array[col][row] << " in DP table\n";
            dp[col][row] = array[col][row];
            return;
        } else {
            // figure out the best to our left
            // and the best to our right
            dpGo(row+1,col);
            dpGo(row+1,col+1);
            // choose the larger
            // cout << "comparing " << dp[col][row+1] << " and " << dp[col+1][row+1] << "\n";
            if (dp[col][row+1] >= dp[col+1][row+1]) {
                // cout << "chose left val " << dp[col][row+1] << "\n";
                dp[col][row] = dp[col][row+1] + array[col][row];
            } else {
                // cout << "chose right " << dp[col+1][row+1] << "\n";
                dp[col][row] = dp[col+1][row+1] + array[col][row];
            }
        }
    }
    return;
}
