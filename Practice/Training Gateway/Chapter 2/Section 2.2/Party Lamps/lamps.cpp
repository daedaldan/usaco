/*
ID: daniel25
TASK: lamps
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>

using namespace std;

struct state {
    bool check = true;
    bool lamps[101];
};

int N;

bool binaryComp(bool const a[], bool const b[]) {
    for (int i = 1; i <= N; i++)
        if (a[i] == b[i])
            continue;
        else
            return a[i] < b[i];
}

struct comp {
    bool operator()(const state & a, const state & b) {return binaryComp(a.lamps, b.lamps);}
};


int C;
int on[100];
int off[100];
int numOn = 0;
int numOff = 0;
bool lamps[101];
set<state, comp> possibleEnds;
int numPossibleEnds = 0;

void all(bool l[]) {
    for (int i = 1; i <= N; i++)
        l[i] = !l[i];
}

void odd(bool l[]) {
    for (int i = 1; i <= N; i+=2)
        l[i] = !l[i];
}

void even(bool l[]) {
    for (int i = 2; i <= N; i+=2)
        l[i] = !l[i];
}

void special(bool l[]) {
    for (int i = 1; i <= N; i+=3)
        l[i] = !l[i];
}

state check(int ops[], bool l[]) {
    state s;
    bool orig[101];
    for (int i = 1; i <= N; i++)
        orig[i] = l[i];
    if (ops[0] == 1)
        all(orig);
    if (ops[1] == 1)
        odd(orig);
    if (ops[2] == 1)
        even(orig);
    if (ops[3] == 1)
        special(orig);
    for (int i = 0; i < numOn; i++) {
        if (orig[on[i]])
            continue;
        else {
            s.check = false;
            return s;
        }
    }
    for (int i = 0; i < numOff; i++) {
        if (!orig[off[i]])
            continue;
        else {
            s.check = false;
            return s;
        }
    }
    for (int i = 1; i <= N; i++)
        s.lamps[i] = orig[i];
    return s;
}

int main() {
    // reading input
    ifstream fin("lamps.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 1; i <= N; i++)
            lamps[i] = true;
        fin >> C;
        int a = 0;
        fin >> a;
        while (a != -1) {
            on[numOn] = a;
            numOn++;
            fin >> a;
        }
        a = 0;
        fin >> a;
        while (a != -1) {
            off[numOff] = a;
            numOff++;
            fin >> a;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 1; i <= N; i++)
        lamps[i] = true;

    // try all possible configurations
    int ops[4];
    for (int a = 0; a <= 1; a++) {
        ops[0] = a;
        for (int b = 0; b <= 1; b++) {
            ops[1] = b;
            for (int c = 0; c <= 1; c++) {
                ops[2] = c;
                for (int d = 0; d <= 1; d++) {
                    ops[3] = d;
                    // check if # of buttons pressed matches given # of button presses
                    if (ops[0] + ops[1] + ops[2] + ops[3] <= C) {
                        state s = check(ops, lamps);
                        // check if configuration is valid
                        if (s.check) {
                            for (int i = 1; i <= N; i++)
                                cout << s.lamps[i];
                            cout << endl;
                            // add to solution set
                            possibleEnds.insert(s);
                        }
                    }
                }
            }
        }
    }

    // writing output
    ofstream fout("lamps.out");
    if (fout.is_open()) {
        if (possibleEnds.empty()) {
            fout << "IMPOSSIBLE" << "\n";
        } else {
            set<state>::iterator it;
            int i = 0;
            for (it = possibleEnds.begin(); it != possibleEnds.end(); ++it) {
                i++;
                if (i % 2 == 0) continue;
                for (int j = 1; j <= N; j++) {
                    if (it->lamps[j])
                        fout << "1";
                    else
                        fout << "0";
                }
                fout << "\n";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}