#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int moves[100001];
int cows[100001];
int zeros[100001];
int numZeros = 0;

int main() {
    // reading input
    ifstream fin("shuffle.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 1; i <= N; i++) {
            fin >> moves[i];
        }
        for (int i = 1; i <= N; i++) {
            cows[i] = 1;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 1; i <= N; i++) {
        cows[i]--;
        cows[moves[i]] += 1;
        if (cows[i] == 0)
            zeros[i] = 1;
    }

    for (int i = 1; i <= N; i++) {
        if (zeros[i] == 1)
            numZeros++;
    }

    // writing output
    ofstream fout("shuffle.out");
    if (fout.is_open()) {
        fout << numZeros << endl;
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}