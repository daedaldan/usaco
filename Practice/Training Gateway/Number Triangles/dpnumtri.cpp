/*
ID: daniel25
TASK: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int R;
int rows[1000][1000];
int dp[1000][1000];
int largest = -1;

int maxInt(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int solve(int row, int i) {
    if (dp[row][i] != -1)
        return dp[row][i];
    if (row < R)
        return dp[row][i] = rows[row][i] + maxInt(solve(row+1, i), solve(row+1, i+1));
    return 0;
}

int main() {
    ifstream fin("numtri.in");
    string line;
    int rowsIndex = 1;
    if (fin.is_open()) {
        getline(fin, line);
        R = stoi(line);
        for (rowsIndex; rowsIndex <= R; rowsIndex++) {
            for (int i = 0; i < rowsIndex; i++)
                fin >> rows[rowsIndex-1][i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            dp[i][j] = -1;

    largest = solve(0, 0);

    ofstream fout("numtri.out");
    if (fout.is_open()) {
        fout << largest << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}