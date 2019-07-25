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
set<int> bisquares;

void initBisquares() {
	for (int p = 0; p <= M; p++)
		for (int q = 0; q <= M; q++)
			bisquares.insert(p*p + q*q);
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

	

	ofstream fout("ariprog.out");
	if (fout.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	fout.close();
}