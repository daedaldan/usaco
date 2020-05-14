#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int N, B;
int f[250], s[250], d[250];
int best = 250;

void solve(int pair, int tile) {
    // update best and return if at end of path
    if (tile >= N - 1) {
        cout << pair << endl;
        best = min(pair, best);
        return;
    }

    // try going forward
    for (int i = tile + 1; i <= tile + d[pair]; i++)
        if (f[i] <= s[pair] && i < N)
            solve(pair, i);
        else
            break;

    // try switching boots
    for (int i = pair + 1; i < B; i++)
        if (f[tile] <= s[i])
            solve(i, tile);
}

int main() {
    // reading input
    ifstream fin("snowboots.in");
    if (fin.is_open()) {
        fin >> N >> B;
        for (int i = 0; i < N; i++)
            fin >> f[i];
        for (int i = 0; i < B; i++)
            fin >> s[i] >> d[i];
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