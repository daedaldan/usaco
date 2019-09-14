/*
ID: daniel25
TASK: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct ariProg {
    int start;
    int step;
};

int N, M = -1;
set<int> bisquaresSet;
int bisquares[62500];
unordered_set<int> bisquare_hash;
int bisquaresIndex = 0;
ariProg ariProgs[10000];
int ariProgIndex = 0;

bool compareAriProgs(ariProg prog1, ariProg prog2) {
    if (prog1.step < prog2.step)
        return true;
    else if (prog1.step == prog2.step && prog1.start < prog2.start)
        return true;
    else
        return false;
}

void initBisquares() {
    for (int p = 0; p <= M; p++)
        for (int q = 0; q <= M; q++)
            bisquaresSet.insert(p*p + q*q);
}

bool search(int a, int b) {
    for (int i = 0; i < N-1; i++) {
        if (bisquare_hash.find(a+b) == bisquare_hash.end())
            return false;
        a = a+b;
    }
    cout << a << endl;
    return true;
}

void findProgs() {
    cout << bisquaresIndex << " bisquares" << endl;
    for (int a = 0; a < bisquaresIndex; a++) {
//        if (bisquares[a] > 12000) cout << bisquares[a] << endl;
        for (int b = a+1; b < bisquaresIndex-1; b++) {
            if (bisquares[b] - bisquares[a] > 5000) continue;
            if (search(bisquares[a], bisquares[b]-bisquares[a])) {
                ariProg ap;
                ap.start = bisquares[a];
                ap.step = bisquares[b]-bisquares[a];
                ariProgs[ariProgIndex] = ap;
                ariProgIndex++;
            }
        }
    }
}

int main() {
    ifstream fin("ariprog.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> M;
    } else {
        cout << "error opening input file" << endl;
    }
    fin.close();

    initBisquares();
    set<int>::iterator it;
    for (it = bisquaresSet.begin(); it != bisquaresSet.end(); ++it) {
        bisquares[bisquaresIndex] = *it;
        bisquare_hash.insert(*it);
        bisquaresIndex++;
    }

    cout << "initialized bisquares" << endl;

    findProgs();

    sort(ariProgs, ariProgs+ariProgIndex, compareAriProgs);

    ofstream fout("ariprog.out");
    if (fout.is_open()) {
        if (ariProgIndex == 0)
            fout << "NONE\n";
        for (int i = 0; i < ariProgIndex; i++)
            fout << ariProgs[i].start << " " << ariProgs[i].step << "\n";
    } else {
        cout << "error opening output file" << endl;
    }
    fout.close();
}