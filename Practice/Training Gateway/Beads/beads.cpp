/*
ID: daniel25
TASK: beads
LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

int readLeft(string leftHalf, char match) {
	if (leftHalf.length() > 1) {
		if (match == '\0' && leftHalf[leftHalf.length()-1] == 'w') {
			return 1 + readLeft(leftHalf.substr(0, leftHalf.length() - 1), match);
		} else if (match == '\0') {
			match = leftHalf[leftHalf.length()-1];
			return 1 + readLeft(leftHalf.substr(0, leftHalf.length() - 1), match);
		} else if (match == leftHalf[leftHalf.length()-1] || leftHalf[leftHalf.length()-1] == 'w') {
			return 1 + readLeft(leftHalf.substr(0, leftHalf.length() - 1), match);
		} else {
			return 0;
		}
	} else {
		if (leftHalf[0] == match || match == '\0' || leftHalf[0] == 'w') {
			return 1;
		} else {
			return 0;
		}
	}
}

int readRight(string rightHalf, char match) {
	if (rightHalf.length() > 1) {
		if (match == '\0' && rightHalf[0] == 'w') {
			return 1 + readRight(rightHalf.substr(1, rightHalf.length()), match);
		} else if (match == '\0') {
			match = rightHalf[0];
			return 1 + readRight(rightHalf.substr(1, rightHalf.length()), match);
		} else if (match == rightHalf[0] || rightHalf[0] == 'w') {
			return 1 + readRight(rightHalf.substr(1, rightHalf.length()), match);
		} else {
			return 0;
		}
	} else {
		if ((rightHalf[0] == match || match == '\0' || rightHalf[0] == 'w') && (rightHalf.length() != 0)) {
			return 1;
		} else {
			return 0;
		}
	}
}

int main() {
	ifstream reader("beads.in");
	// ifstream reader("input.txt");
	string strNumBeads;
	int numBeads = -1;
	string necklace;
	if (reader.is_open()) {
		getline(reader, strNumBeads);
		numBeads = stoi(strNumBeads);
		getline(reader, necklace);
	} else {
		cout << "error opening input file" << endl;
	}

	// doubling the necklace to simulate being able to loop around the ends
	string doubleNecklace = necklace + necklace;
	// division point between the two copies of the necklace
	// this int is the index of the last bead of the first half
	int split = numBeads - 1;

	int maxBeads = -1;

	// iterate through all possible splits of necklace
	for (int i = 0; i < numBeads; i++) {
		int foundBeads = 0;
		foundBeads += readLeft(doubleNecklace.substr(0, split + 1), '\0');
		cout << "readLeft: " << foundBeads << endl;
		foundBeads += readRight(doubleNecklace.substr(split + 1, doubleNecklace.length() / 2 - foundBeads), '\0');
		cout << "after readRight: " << foundBeads << endl;
		if (foundBeads > maxBeads) {
			maxBeads = foundBeads;
		}
		doubleNecklace = doubleNecklace.substr(1, doubleNecklace.length()) + doubleNecklace[0];
	}

	ofstream writer("beads.out");
	// ofstream writer("output.txt");
	if (writer.is_open()) {
		writer << maxBeads << "\n";
	} else {
		cout << "error opening output file" << endl;
	}

	return 0;
}