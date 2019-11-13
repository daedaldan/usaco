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

void initializeDP() {
    // setting all values in dp array to -1
    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = -1;
        }
    }

    // setting base cases for 0 dollars
    for (int i = 0; i < V; i++) {
        dp[i][0] = 0;
    }

    // setting base cases for 0 coins
    for (int i = 0; i < N; i++) {
        dp[0][i] = 0;
    }

    // setting base cases for each coin
    int sumCoins = 0;
    for (int i = 1; i <= V; i+=1) {
        sumCoins += coins[i-1];
        dp[i][sumCoins] = 1;
    }
}

int solve(int c, int m, int layer) {
    if (dp[c][m] != -1) {
        return dp[c][m];
    } else {
        int sum = 0;
        int i = 1;
            for (int j = coins[0]; j < m / 2; j += coins[i-1]) {
                // left includes coin
                sum += solve(c, m - j, layer+1) + solve(c-1, j, layer+1);
                // right includes coin
                sum += solve(c-1, m - j, layer+1) + solve(c, j, layer+1);
                // both include coin
                sum += solve(c, m - j, layer+1) + solve(c, j, layer+1);
                if (i != c)
                    i++;
            }
        dp[c][m] = sum;
        for (int i = 0; i < layer; i++)
            cout << "   ";
        cout << sum << " ways to make " << m << " dollars with " << c << " coins" << endl;
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

    initializeDP();

    solutions = solve(V, N, 0) + 1;

    for (int i = 0; i <= V; i++) {
        for (int j = 0; j <= N; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // writing output
    ofstream fout("money.out");
    if (fout.is_open()) {
        fout << solutions << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}