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
long long creatable[40][781];
long long solutions = 0;

int fillCreatable() {
    for (int i = 2; i <= N; i++) {
        int j = 0;
        while (creatable[i-1][j] >= 1) {
            creatable[i][j] += creatable[i-1][j];
            creatable[i][j+i] += creatable[i-1][j];
            j++;
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

    if (goal % 2 == 1) {
        ;
    } else {
        goal /= 2;
        creatable[0][0] = 1;
        creatable[1][0] = 1;
        creatable[1][1] = 1;
        fillCreatable();
        solutions = creatable[N][goal];
        solutions /= 2;
    }
    for (int i = 0; i <= N; i++) {
        cout << i << ": ";
        for (int j = 0; j <= goal*2; j++) {
            cout << creatable[i][j] << " ";
        }
        cout << endl;
    }

    // writing output
    ofstream fout("subset.out");
    if (fout.is_open()) {
        fout << solutions << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}