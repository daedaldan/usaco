#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

int N;
int moves[100001];
int shuffled[100001];
queue<int> deadPosition;
int numZeroes = 0;

int main() {
    // reading input
    ifstream fin("shuffle.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 1; i <= N; i++) {
            fin >> moves[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 1; i <= N; i++) {
        shuffled[moves[i]] += 1;
    }

    for (int i = 1; i <= N; i++) {
        if (shuffled[i] == 0) {
            deadPosition.push(i);
            numZeroes++;
        }
    }

    while (!deadPosition.empty()) {
        int current = deadPosition.front();
        deadPosition.pop();
        shuffled[moves[current]] -= 1;
        if (shuffled[moves[current]] == 0) {
            deadPosition.push(moves[current]);
            numZeroes++;
        }
    }


    // writing output
    ofstream fout("shuffle.out");
    if (fout.is_open()) {
        fout << N - numZeroes << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}