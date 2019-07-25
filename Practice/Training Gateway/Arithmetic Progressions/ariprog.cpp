/*
ID: daniel25
TASK: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int N, M = -1;
set<int> bisquaresSet;
int bisquares[62500];
int bisquaresIndex = 0;
int ariProgs[10000][2];
int ariProgIndex = 0;

void initBisquares() {
	for (int p = 0; p <= M; p++)
		for (int q = 0; q <= M; q++)
			bisquaresSet.insert(p*p + q*q);
}

int sumBefore(int i) {
	int sum = 0;
	for (int j = i; j >= 1; j--)
		sum += j;
	return sum;
}

void findProgs() {
	for (int a = 0; a < bisquaresIndex; a++) {
		for (int b = 0; b < bisquaresIndex; b++) {
			for (int total = 0; total < bisquaresIndex; total++) {
				if ((bisquares[a] * N + bisquares[b] * sumBefore(N)) == bisquares[total]) {
					ariProgs[ariProgIndex][0] = a;
					ariProgs[ariProgIndex][1] = b;
					ariProgIndex++;
				}
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

	for (int i = 0; i < bisquaresIndex; i++)
		cout << bisquares[i] << endl;

	findProgs();

	ofstream fout("ariprog.out");
	if (fout.is_open()) {
		for (int i = 0; i < ariProgIndex; i++)
			fout << ariProgs[i][0] << " " << ariProgs[i][1] << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	fout.close();
}