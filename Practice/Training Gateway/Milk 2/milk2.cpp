/*
ID: daniel25
TASK: milk2
LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	// ifstream reader("milk2.in");
	ifstream reader("input.txt");
	if (reader.is_open()) {

	} else {
		cout << "error opening input file" << endl;
	}


	// ofstream writer("milk2.out");
	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}

	return 0;
}