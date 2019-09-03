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
set<vector<bucket>> pastStates;
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
        if (found == true)
            return true;
    }
    return false;
}

void solve(vector<bucket> state) {
    // find non-empty buckets
    for (int i = 0; i < state.size(); i++) {
        if (state[i].milk > 0) {
            // for other buckets
            for (int j = 0; j < state.size(); j++) {
                if (i != j) {

                    if (state[0].milk == 0) {
                        solutions.insert(state[2].milk);
                        cout << state[2].milk << endl;
                        pour(state[i], state[j]);
                        solve(state);
                    }
                    if (!state_find(pastStates, state)) {
                        pastStates.insert(state);
                        pour(state[i], state[j]);
                        solve(state);
                    } else
                        return;
//                    solve(state);
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

    solve(buckets);

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