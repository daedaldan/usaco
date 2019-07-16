/*
ID: daniel25
TASK: crypt1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void threeDigitPermutations(vector<string> & digits, vector<string> & permutations, string soFar) {
	if (soFar.size() == 3) {
		permutations.push_back(soFar);
	} else {
		for (int i = 0; i < digits.size(); i++) {
			threeDigitPermutations(digits, permutations, soFar + digits[i]);
		}
	}
}

void twoDigitPermutations(vector<string> & digits, vector<string> & permutations, string soFar) {
		if (soFar.size() == 2) {
		permutations.push_back(soFar);
	} else {
		for (int i = 0; i < digits.size(); i++) {
			twoDigitPermutations(digits, permutations, soFar + digits[i]);
		}
	}
}

int main() {
	// reading input
	ifstream reader("input.txt");
	string strNumDigits;
	string line2;
	// number of possible digits
	int numDigits = -1;
	// vector possible digits from input
	vector<int> possibleDigits;
	if (reader.is_open()) {
		getline(reader, strNumDigits);
		numDigits = stoi(strNumDigits);
		getline(reader, line2);
		stringstream ss(line2);
		string token;
		while(getline(ss, token, ' '))
			possibleDigits.push_back(stoi(token));
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	vector<string> strPossibleDigits;
	for (int i = 0; i < possibleDigits.size(); i++)
		strPossibleDigits.push_back(to_string(possibleDigits[i]));

	// calculate all possible permutations of three and two digit numbers using input
	vector<string> threeDigit;
	threeDigitPermutations(strPossibleDigits, threeDigit, "");

	vector<string> twoDigit;
	twoDigitPermutations(strPossibleDigits, twoDigit, "");

	// cout << 420 << endl;

	cout << threeDigit[0] << endl;
	cout << twoDigit[0][1] << endl;
	cout << stoi(threeDigit[0]) * stoi(to_string(twoDigit[0][1])) << endl;
	cout << to_string(stoi(threeDigit[0]) * stoi(to_string(twoDigit[0][0]))) << endl;
	// find valid permutations
	for (int i = 0; i < threeDigit.size(); i++) {
		for (int j = 0; j < twoDigit.size(); j++) {
			bool validPerm = true;
			string partialProduct1 = to_string(stoi(threeDigit[i]) * stoi(to_string(twoDigit[i][1])));
			string partialProduct2 = to_string(stoi(threeDigit[i]) * stoi(to_string(twoDigit[i][0])));
			string product = to_string(stoi(partialProduct1) + stoi(partialProduct2 + "0"));
			if (partialProduct1.size() != 3)
				validPerm = false;
			else if (partialProduct2.size() != 3)
				validPerm = false;
			else if (product.size() != 4)
				validPerm = false;
			else {
				cout << 420 << endl;
				for (int k = 0; k < product.size(); k++) {
					if (find(strPossibleDigits.begin(), strPossibleDigits.end(), to_string(product[k])) == strPossibleDigits.end()) {
						validPerm = false;
						break;
					}
				}
			}
			if (validPerm) {
				cout << partialProduct1 << endl;
				cout << partialProduct2 << endl;
				cout << product << endl;
			}
		}
	}


	// writing output
	ifstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}