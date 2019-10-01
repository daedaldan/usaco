/*
ID: daniel25
TASK: sort3
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int have[1000];
int want[1000];

void swap(int a, int b, int arr[]) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int main() {
    // reading input
    ifstream fin("sort3.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            fin >> have[i];
            want[i] = have[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(want, want+N);

    // swaps correcting two elements
    int nswap = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (have[i] != want[i] && have[j] != want[j]
            && have[i] == want[j] && have[j] == want[i]) {
                have[i] = want[i];
                have[j] = want[j];
                nswap++;
            }
        }
    }

    int nbad = 0;
    for (int i = 0; i < N; i++)
        if (have[i] != want[i])
            nbad++;

    nswap += nbad/3 * 2;

    // writing output
    ofstream fout("sort3.out");
    if (fout.is_open()) {
        fout << nswap << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}