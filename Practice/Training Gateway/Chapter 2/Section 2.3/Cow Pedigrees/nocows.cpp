/*
ID: daniel25
TASK: nocows
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int K;
int dp[101][201];
long solution;

long solve(int levels, int nodes) {
    cout << levels << " " << nodes << endl;
    if (dp[levels][nodes] != 0) {
        return dp[levels][nodes];
    } else {
        for (int i = 0; i < nodes; i++) {
            dp[levels][nodes] += solve(levels-1, i) + (levels-1, nodes-i-1);
        }
        return dp[levels][nodes];
    }
}

int main() {
    // reading input
    ifstream fin("nocows.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> K;
    } else cout << "error opening input file" << endl;
    fin.close();

    if (N % 2 == 0) {
        ;
    } else {
        N /= 2;
        K -= 1;

        for (int i = 0; i <= K; i++)
            dp[i][0] = 1;

        solution = solve(N, K) - solve(N, K-1);
    }

    // writing output
    ofstream fout("nocows.out");
    if (fout.is_open()) {
        fout << solution % 9901 << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}