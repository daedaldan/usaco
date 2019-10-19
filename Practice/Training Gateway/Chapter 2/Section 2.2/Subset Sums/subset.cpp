/*
ID: daniel25
TASK: subset
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct subsets {
    int nextAdd = 1;
    int leftSum = 0;
    int rightSum = 0;
    bool visited = false;
};

int N;
int goal;
subsets sums[40][40];
int equalSums = 0;
int found[1000][1000];

void printSums() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << sums[i][j].leftSum << "," << sums[i][j].rightSum << " ";
        }
        cout << endl;
    }
}

void fillSums(int row, int col, bool right) {
    if (sums[row][col].nextAdd == N+1 && sums[row][col].leftSum == sums[row][col].rightSum)
        cout << sums[row][col].leftSum << " " << sums[row][col].rightSum << endl;
    if (!(row == 0 && col == 0)) {
        if (right) {
            sums[row][col].leftSum = sums[row][col-1].leftSum;
            sums[row][col].rightSum = sums[row][col-1].rightSum;
            sums[row][col].rightSum += sums[row][col-1].nextAdd;
            sums[row][col].nextAdd = sums[row][col-1].nextAdd+1;
        } else {
            sums[row][col].leftSum = sums[row-1][col].leftSum;
            sums[row][col].rightSum = sums[row-1][col].rightSum;
            sums[row][col].leftSum += sums[row-1][col].nextAdd;
            sums[row][col].nextAdd = sums[row-1][col].nextAdd+1;
        }
        sums[row][col].visited = true;
    }

    if (sums[row][col].nextAdd <= N) {
        fillSums(row, col+1, true);
        fillSums(row+1, col, false);
    } else {
        if (sums[row][col].leftSum == sums[row][col].rightSum) {
            found[row][col] = 1;
            equalSums++;
        }
    }
}

int main() {
    // reading input
    ifstream fin("subset.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 1; i <= N; i++) {
        goal += i;
    }

    printSums();

    fillSums(0, 0, false);

    cout << endl;
    printSums();

    // writing output
    ofstream fout("subset.out");
    if (fout.is_open()) {
        fout << equalSums / 2 << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}