/*
ID: daniel25
TASK: dualpal
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>

using namespace std;

bool isPalindrome(string s) {
	if (s.size() == 1 || s.size() == 0)
		return true;
	else if (s[0] == s[s.size()-1])
		return isPalindrome(s.substr(1, s.size()-2));
	else 
		return false;
}

string baseTransform(string s, int base) {
	string transformed;
	int num = stoi(s);
	int dividend = num;
	int quotient = -1;
	map<int, string> bigBase;
	bigBase[10] = "A";
	bigBase[11] = "B";
	bigBase[12] = "C";
	bigBase[13] = "D";
	bigBase[14] = "E";
	bigBase[15] = "F";
	bigBase[16] = "G";
	bigBase[17] = "H";
	bigBase[18] = "I";
	bigBase[19] = "J";
	bigBase[20] = "K";
	while (quotient != 0) {
		if (dividend % base > 9) {
			transformed += bigBase[dividend % base];
		} else {
			transformed += to_string(dividend % base);
		}
		quotient = floor(dividend / base);
		dividend = quotient;
	}

	string copy = transformed;
	transformed = "";

	for (int i = copy.size() - 1; i >= 0; i--)
		transformed += copy[i];

	return transformed;
} 

int main() {
	// ifstream reader("input.txt");
	ifstream reader("dualpal.in");
	string inputLine;
	int firstN = -1;
	int greaterThan = -1;
	if (reader.is_open()){
		getline(reader, inputLine);
		firstN = stoi(inputLine.substr(0, inputLine.find(" ")));
		greaterThan = stoi(inputLine.substr(inputLine.find(" ")));
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	vector<int> dualPalindromes;
	int found = 0;
	int num = greaterThan + 1;

	while (found < firstN) {
		bool palin1 = false;
		bool palin2 = false;
		for (int i = 2; i <= 10; i++) {
			if (isPalindrome(baseTransform(to_string(num), i))) {
				if (palin1) {
					palin2 = true;
					found += 1;
					dualPalindromes.push_back(num);
					break;
				} else {
					palin1 = true;
				}
			}
		}
		num += 1;
	}

	// ofstream writer("output.txt");
	ofstream writer("dualpal.out");
	if (writer.is_open()) {
		for (int i = 0; i < dualPalindromes.size(); i++) {
			writer << dualPalindromes[i] << "\n";
		}
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}