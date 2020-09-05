#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct boot {
    int depth;
    int step;
};

int N, B;
int snow[250];
boot boots[250];
int best = 9999;
int beenthere[250][250];

void solve(int t, int b) {
    // check if have visited this state before
    if (beenthere[t][b])
        return;
    beenthere[t][b] = 1;

    // if done
    if (t == N - 1) {
        if (b < best) {
            best = b;
            return;
        }
    }

    // try walking forward
    for (int i = 1; i <= boots[b].step; i++) {
        if (t + i < N && snow[t + i] <= boots[b].depth) {
            solve(t + i, b);
        }
    }

    // try switching boots
    for (int i = b + 1; i < B; i++) {
        if (boots[i].depth >= snow[t]) {
            solve(t, i);
        }
    }
}

int main() {
    // reading input
    ifstream fin("snowboots.in");
    if (fin.is_open()) {
        fin >> N >> B;
        for (int i = 0; i < N; i++) {
            fin >> snow[i];
        }
        for (int i = 0; i < B; i++) {
            fin >> boots[i].depth >> boots[i].step;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    solve(0, 0);

    // writing output
    ofstream fout("snowboots.out");
    if (fout.is_open()) {
        fout << best << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}