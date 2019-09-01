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

using namespace std;

struct ariProg {
    int start;
    int step;
};

int N, M = -1;
set<int> bisquaresSet;
int bisquares[62500];
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
        if (bisquaresSet.find(a+b) == bisquaresSet.end())
            return false;
        a = a+b;
    }

    return true;
}

void findProgs() {
	for (int a = 0; a < bisquaresIndex; a++) {
		for (int b = a+1; b < bisquaresIndex-1; b++) {
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
        bisquaresIndex++;
    }

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