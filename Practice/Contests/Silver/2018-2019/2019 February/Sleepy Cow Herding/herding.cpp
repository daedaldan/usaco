#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int N, cows[100000];
int low, high;

int main() {
    // reading input
    ifstream fin("herding.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++)
            fin >> cows[i];
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(cows, cows+N);

    // solve for min
    if (cows[N-2] - cows[0] == N-2 && cows[N-1] - cows[N-2] > 2) {
        low = 2;
    } else if (cows[N-1] - cows[1] == N-2 && cows[1] - cows[0] > 2) {
        low = 2;
    } else {
        int j = 0;
        int best = 0;
        for (int i = 0; i < N; i++) {
            while (j < N-1 && cows[j+1]-cows[i] <= N-1) j++;
            best = max(best, j-i+1);
        }
        low = N - best;
    }

    // solve for max
    int gaps = 0;
    for (int i = 1; i < N; i++) {
        gaps += cows[i] - cows[i-1] - 1;
    }
    high = gaps - min(cows[1] - cows[0] - 1, cows[N-1] - cows[N-2] - 1);

    // writing output
    ofstream fout("herding.out");
    if (fout.is_open()) {
        fout << low << "\n" << high << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}