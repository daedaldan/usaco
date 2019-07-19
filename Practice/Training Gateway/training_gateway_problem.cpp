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
	ifstream reader("input.txt");
	if (reader.is_open()) {

	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	// writing output
	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
}