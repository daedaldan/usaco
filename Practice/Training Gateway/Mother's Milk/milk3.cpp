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

struct state {
    int milk[3];
};

set<int> solutions;
int seen[21][21][21];
int size[3];

state newState(int a, int b, int c) {
    state s;

    s.milk[0] = a;
    s.milk[1] = b;
    s.milk[2] = c;

    return s;
}

state pour(state s, int from, int to) {
    int amt = s.milk[from];
    if (s.milk[to] + amt > size[to])
        amt = size[to] - s.milk[to];

    s.milk[from] -= amt;
    s.milk[to] += amt;

    return s;
}

void solve(state s) {
//    cout << "here" << endl;

    if (seen[s.milk[0]][s.milk[1]][s.milk[2]] == 1) return;

    seen[s.milk[0]][s.milk[1]][s.milk[2]] = 1;

    if (s.milk[0] == 0)
        solutions.insert(s.milk[2]);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            solve(pour(s, i, j));
}

int main() {
    ifstream fin("milk3.in");
    string hi;
    if (fin.is_open()) {
        fin >> size[0];
        fin >> size[1];
        fin >> size[2];
    } else cout << "error opening input file" << endl;
    fin.close();

    solve(newState(0, 0, size[2]));

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