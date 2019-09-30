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
#include <iterator>

using namespace std;

int N;
int records[1000];
int minExchanges = 99999;

struct state {
    int exchanges = 0;
    int nums[1000];
};

void swap(int a, int b, state & s) {
    int temp = s.nums[a];
    s.nums[a] = s.nums[b];
    s.nums[b] = temp;
    s.exchanges++;
}

bool sorted(state s) {
//    for (int i = 0; i < N; i++)
//        cout << s.nums[i] << " ";
//    cout << endl;
    for (int i = 0; i < N-1; i++) {
        if (s.nums[i] > s.nums[i+1])
            return false;
    }

    return true;
}

int process(state s, queue<state> unprocessed) {
    if (sorted(s)) {
        cout << "       HERE " << endl;
        minExchanges = s.exchanges;
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            state sCopy = s;
            if (sCopy.nums[i] != sCopy.nums[j]) {
                if (sCopy.exchanges == 1 && i == 4 && j == 6)
                    cout << "step 2" << endl;
                swap(i, j, sCopy);
                unprocessed.push(sCopy);
            }
        }
    }
}

void bfs() {
    queue<state> unprocessed;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            state s = state();
            copy(begin(records), end(records), begin(s.nums));
            if (s.nums[i] != s.nums[j])
                swap(i, j, s);
            if (i == 0 && j == 3)
                cout << "step 1" << endl;
            unprocessed.push(s);
        }
    }

    while (!unprocessed.empty()) {
        state next = unprocessed.front();
        unprocessed.pop();
        if (process(next, unprocessed) == 1) {
            cout << "here" << endl;
            return;
        }
    }
}

int main() {
    // reading input
    ifstream fin("sort3.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++)
            fin >> records[i];
    } else cout << "error opening input file" << endl;
    fin.close();

    bfs();

    // writing output
    ofstream fout("sort3.out");
    if (fout.is_open()) {
        fout << minExchanges << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}