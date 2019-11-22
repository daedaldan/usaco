/*
ID: daniel25
TASK: taskname
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	// reading input
	ifstream fin("input.in");
	if (fin.is_open()) {

	} else cout << "error opening input file" << endl;
	fin.close();

	// writing output
	ofstream fout("output.out");
	if (fout.is_open()) {

	} else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}