/*
ID: daniel25
TASK: money
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int V;
int N;
int coins[25];
int dp[25][10000];
int solutions;

int solve(int c, int m) {
    if (dp[c][m] != -1) {
        cout << c << " " << m << endl;
        cout << "   " << dp[c][m] << endl;
        return dp[c][m];
    } else {
        int sum = 0;
        for (int i = 1; i < c; i++) {
            for (int j = 0; j <= m; j += coins[i]) {
                sum += solve(i-1, m - j) + solve(i-1, j) + 1;
            }
        }
        dp[c][m] = sum;
        cout << c << " " << m << endl;
        cout << "   " << sum << endl;
        return sum;
    }
}

int main() {
    // reading input
    ifstream fin("money.in");
    if (fin.is_open()) {
        fin >> V;
        fin >> N;
        for (int i = 0; i < V; i++) {
            fin >> coins[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // setting all values in dp array to -1

    // setting base cases for 0 dollars
    for (int i = 0; i < V; i++) {
        dp[i][0] = 0;
    }

    // setting base cases for each coin
    for (int i = 1; i <= V; i++) {
        dp[i][coins[i]] = 1;
    }

    solutions = solve(V, N) + 1;

    // writing output
    ofstream fout("money.out");
    if (fout.is_open()) {
        fout << solutions << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}