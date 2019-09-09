/*
ID: daniel25
TASK: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct bucket {
    int milk;
    int size;
};

bool operator==(const bucket & a, const bucket & b) {
    return (a.milk == b.milk && a.size == b.size);
}

bool operator<(const bucket & a, const bucket & b) {
    return a.milk < b.milk;
}

int A, B, C = 0;
set<int> solutions;
vector<bucket> buckets;

void pour(bucket & a, bucket & b) {
    while (a.milk != 0 && b.milk < b.size) {
        b.milk += 1;
        a.milk -= 1;
    }
}

bool state_find(set<vector<bucket>> & states, vector<bucket> & state) {
    set<vector<bucket>>::iterator it;
    for (it = states.begin(); it != states.end(); ++it) {
        bool found = false;
        for (int i = 0; i < 3; i++) {
            if ((*it)[i].milk == state[i].milk && (*it)[i].size == state[i].size)
                found = true;
            else
                found = false;
        }
        if (found)
            return true;
    }
    return false;
}

void solve(vector<bucket> state, set<vector<bucket>> past, int depth) {
    // find non-empty buckets
    for (int i = 0; i < state.size(); i++) {
        if (state[i].milk > 0) {
            // for other buckets
            for (int j = 0; j < state.size(); j++) {
//                bucket ij1;
//                bucket ij2;
//                ij1.size = -1;
//                ij1.milk = i;
//                ij2.size = -1;
//                ij2.milk = j;
//                state.push_back(ij1);
//                state.push_back(ij2);
//                if (depth == 0 && j == 1) cout << "          HEREEEEE" << endl;
                if (i != j) {
//                    cout << "depth: " << depth << endl;
//                    cout << state[0].milk << ", " << state[0].size << " | ";
//                    cout << state[1].milk << ", " << state[1].size << " | ";
//                    cout << state[2].milk << ", " << state[2].size << " | ";
//                    cout << endl;
//                    cout << "using buckets: " << i << ", " << j << endl;
//                    if ((state[0].milk == 8 && state[1].milk == 1 && state[2].milk == 1) && i == 0 && j == 2)
//                        cout << i << " " << j << endl;
                    // if A is empty, save the solution and adjust
                    if (state[0].milk == 0) {
//                        if ((state[0].milk == 8 && state[1].milk == 1 && state[2].milk == 1) && i == 0 && j == 2)
//                            cout << 234 << endl;
                        solutions.insert(state[2].milk);
//                        cout << "solution: " << state[2].milk << endl;
                        vector<bucket> newState;
                        for (int k = 0; k < 3; k++) {
                            bucket a;
                            a.milk = state[k].milk;
                            a.size = state[k].size;
                            newState.push_back(a);
                        }
                        pour(newState[i], newState[j]);
                        solve(newState, past, ++depth);
                    } // if this state has not been found before, save it (to prevent infinite loops)
                    if (!state_find(past, state)) {
//                        if ((state[0].milk == 8 && state[1].milk == 1 && state[2].milk == 1) && i == 0 && j == 2)
//                            cout << 234 << endl;
                        past.insert(state);
                        vector<bucket> newState;
                        for (int k = 0; k < 3; k++) {
                            bucket a;
                            a.milk = state[k].milk;
                            a.size = state[k].size;
                            newState.push_back(a);
                        }
                        pour(newState[i], newState[j]);
                        solve(newState, past, ++depth);
                    } else {
                        if (depth == 0)
                            cout << "HEREEEE" << endl;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    ifstream fin("milk3.in");
    string hi;
    if (fin.is_open()) {
        fin >> A;
        fin >> B;
        fin >> C;
        bucket bucketA;
        bucketA.milk = 0;
        bucketA.size = A;
        buckets.push_back(bucketA);
        bucket bucketB;
        bucketB.milk = 0;
        bucketB.size = B;
        buckets.push_back(bucketB);
        bucket bucketC;
        bucketC.milk = C;
        bucketC.size = C;
        buckets.push_back(bucketC);
    } else cout << "error opening input file" << endl;
    fin.close();

    set<vector<bucket>> pastStates;
    solve(buckets, pastStates, 0);

    ofstream fout("milk3.out");
    if (fout.is_open()) {
        set<int>::iterator it;
        vector<int> vecSolutions;
        for (it = solutions.begin(); it != solutions.end(); ++it)
            vecSolutions.push_back(*it);
        for (int i = 0; i < vecSolutions.size(); i++) {
            if (i != vecSolutions.size()-1)
                fout << vecSolutions[i] << " ";
            else
                fout << vecSolutions[i] << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}