/*
ID: daniel25
TASK: sort3
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

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
    for (int i = 0; i < N-1; i++) {
        if (s.nums[i] > s.nums[i+1])
            return false;
    }

    return true;
}

//int process(state s, queue<state> & unprocessed) {
//    if (sorted(s)) {
//        cout << "       HERE " << endl;
//        for (int i = 0; i < N; i++)
//            cout << s.nums[i] << endl;
//        minExchanges = s.exchanges;
//        return 1;
//    }
//
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            state sCopy = s;
//            if (sCopy.nums[i] != sCopy.nums[j]) {
//                swap(i, j, sCopy);
//                unprocessed.push(sCopy);
//            }
//        }
//    }
//
//    return 0;
//}
//

int capped_dfs(state & s, int lastA, int lastB, int depth) {
    cout << depth << endl;
    if (sorted(s)) {
        minExchanges = s.exchanges;
        return 1;
    }

    if (depth == 0)
        return 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (records[i] != records[j] &&
            lastA != i &&
            lastA != j &&
            lastB != i &&
            lastB != j) {
                state sCopy = state();
                for (int k = 0; k < N; k++)
                    sCopy.nums[k] = records[k];
                swap(i, j, sCopy);
                if (capped_dfs(sCopy, i, j, depth-1) == 1)
                    return 1;
            }
        }
    }

    return 0;
}

void dfs_id(state s) {
    for (int i = 0; i < 500; i++) {
        if (capped_dfs(s, -1, -1, i) == 1)
            return;
    }
}

//int dfs(state & s, int lastA, int lastB) {
//    cout << s.exchanges << endl;
//    if (sorted(s)) {
//        minExchanges = s.exchanges;
//        return 1;
//    }
//
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            if (records[i] != records[j] &&
//            lastA != i &&
//            lastA != j &&
//            lastB != i &&
//            lastB != j) {
//                state sCopy = state();
//                for (int k = 0; k < N; k++)
//                    sCopy.nums[k] = records[k];
//                swap(i, j, sCopy);
//                if (dfs(sCopy, i, j) == 1)
//                    return 1;
//            }
//        }
//    }
//
//    return 0;
//}

int main() {
    // reading input
    ifstream fin("sort3.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++)
            fin >> records[i];
    } else cout << "error opening input file" << endl;
    fin.close();

    state s;
    for (int i = 0; i < N; i++) {
        s.nums[i] = records[i];
    }

    dfs_id(s);

    // writing output
    ofstream fout("sort3.out");
    if (fout.is_open()) {
        fout << minExchanges << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}