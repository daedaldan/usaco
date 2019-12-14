#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N, K;
int sessions[10][20];
int numConsistentPairs = 0;

bool consistent (int a, int b) {
    int betterCow;
    int indexA, indexB;
    for (int i = 0; i < N; i++) {
        if (sessions[0][i] == a)
            indexA = i;
        if (sessions[0][i] == b)
            indexB = i;
    }
    if (indexA < indexB) {
        betterCow = a;
    } else {
        betterCow = b;
    }

    // check every session
    for (int session = 1; session < K; session++) {
        // find indcies of cows being compared
        for (int i = 0; i < N; i++) {
            if (sessions[session][i] == a)
                indexA = i;
            if (sessions[session][i] == b)
                indexB = i;
        }
        // check if they match with first session
        if (betterCow == a) {
            if (indexA < indexB)
                ;
            else
                return false;
        } else {
            if (indexB < indexA)
                ;
            else
                return false;
        }
    }

    // pair of cows is consistent
    return true;
}

int main() {
    // reading input
    ifstream fin("gymnastics.in");
    if (fin.is_open()) {
        fin >> K >> N;
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                fin >> sessions[i][j];
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int cow1 = 1; cow1 <= N; cow1++) {
        for (int cow2 = cow1 + 1; cow2 <= N; cow2++) {
            if (consistent(cow1, cow2)) {
                numConsistentPairs++;
            }
        }
    }

    // writing output
    ofstream fout("gymnastics.out");
    if (fout.is_open()) {
        fout << numConsistentPairs << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}