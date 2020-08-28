/*
ID: daniel25
TASK: barn1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct gap {
    int start;
    int end;
};

int M, S, C;
int stalls[200];
int cows[200];
gap gaps[200];
int numBoards = 1;
int covered = 0;

bool cmp(gap a, gap b) { return a.end - a.start > b.end - b.start; }

int main() {
    // reading input
    ifstream fin("barn1.in");
    if (fin.is_open()) {
        fin >> M >> S >> C;
        for (int i = 0; i < C; i++) {
            fin >> cows[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(cows, cows + C);

    for (int i = cows[0] - 1; i < cows[C - 1]; i++) {
        stalls[i] = 1;
    }

    for (int i = 0; i < C - 1; i++) {
        gaps[i].start = cows[i];
        gaps[i].end = cows[i + 1];
    }

    sort(gaps, gaps + C - 1, cmp);

    while (numBoards < M) {
        for (int i = gaps[numBoards - 1].start; i < gaps[numBoards - 1].end - 1; i++) {
            stalls[i] = 0;
        }

        numBoards++;
    }

    for (int i = 0; i < S; i++) {
        if (stalls[i]) {
            covered++;
        }
    }

    // writing output
    ofstream fout("barn1.out");
    if (fout.is_open()) {
        fout << covered << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}