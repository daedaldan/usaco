/*
ID: daniel25
TASK: palsquare
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <map>

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
	// reading input
	// ifstream reader("input.txt");
	ifstream reader("palsquare.in");
	string strBase;
	int base;
	if (reader.is_open()) {
		getline(reader, strBase);
		base = stoi(strBase);
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	// ofstream writer("output.txt");
	ofstream writer("palsquare.out");

	if (writer.is_open()) {
		for (int i = 1; i <= 300; i++) {
			if (isPalindrome(baseTransform(to_string(i * i), base)))
				writer << baseTransform(to_string(i), base) << " " << baseTransform(to_string(i * i), base) << "\n";
		}
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}