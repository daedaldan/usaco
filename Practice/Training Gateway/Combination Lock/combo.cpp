/*
ID: daniel25
TASK: combo
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

bool close_enough(int a, int b, int range) {
	if (abs(a-b) <= 2)
		return true;
	if (abs(a-range-b) <= 2)
		return true;
	if (abs(b-range-a) <= 2)
		return true;
	return false;
}

int main() {
	// reading input
	string strLockRange;
	int lockRange;
	string strCombo;
	// vectors of ints with Farmer John's and master combination, respectively
	vector<int> combo1;
	vector<int> combo2;
	// ifstream reader("input.txt");
	ifstream reader("combo.in");
	if (reader.is_open()) {
		getline(reader, strLockRange);
		lockRange = stoi(strLockRange);
		getline(reader, strCombo);
		int blank1 = strCombo.find(" ");
		int blank2 = strCombo.find(" ", blank1+1);
		int num1 = stoi(strCombo.substr(0, blank1));
		int num2 = stoi(strCombo.substr(blank1, blank2));
		int num3 = stoi(strCombo.substr(blank2));
		combo1.push_back(num1);
		combo1.push_back(num2);
		combo1.push_back(num3);
		getline(reader, strCombo);
		blank1 = strCombo.find(" ");
		blank2 = strCombo.find(" ", blank1+1);
		num1 = stoi(strCombo.substr(0, blank1));
		num2 = stoi(strCombo.substr(blank1, blank2));
		num3 = stoi(strCombo.substr(blank2));
		combo2.push_back(num1);
		combo2.push_back(num2);
		combo2.push_back(num3);
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	set<vector<int>> validCombos;

	for (int i = 1; i <= lockRange; i++) {
		for (int j = 1; j <= lockRange; j++) {
			for (int k = 1; k <= lockRange; k++) {
				vector<int> combo;
				combo.push_back(i);
				combo.push_back(j);
				combo.push_back(k);
				bool close = true;
				for (int j = 0; j < 3; j++) {
					if (close_enough(combo[j], combo1[j], lockRange))
						continue;
					else {
						close = false;
						break;
					} 
				}
				if (close)
					validCombos.insert(combo);
				close = true;
				for (int j = 0; j < 3; j++) {
					if (close_enough(combo[j], combo2[j], lockRange))
						continue;
					else {
						close = false;
						break;
					} 
				}
				if (close)
					validCombos.insert(combo);
			}
		}
	}

	// writing output
	// ofstream writer("output.txt");
	ofstream writer("combo.out");
	if (writer.is_open()) {
		writer << validCombos.size() << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}