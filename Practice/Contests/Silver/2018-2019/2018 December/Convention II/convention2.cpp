#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct cow {
    int arrival;
    int sampling;
    int seniority;
    bool operator<(const cow & rhs) const {
        return seniority < rhs.seniority;
    }
};

int N;
cow cows[100000];
priority_queue<cow> waiting;

bool arrivalCmp (cow a, cow b) {
    return a.arrival < b.arrival;
}

int main() {
    // reading input
    ifstream fin("convention2.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            cow c;
            fin >> c.arrival;
            fin >> c.sampling;
            c.seniority = N - i;
            cows[i] = c;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(cows, cows+N, arrivalCmp);

    // writing output
    ofstream fout("convention2.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}