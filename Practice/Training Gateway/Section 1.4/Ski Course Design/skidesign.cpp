/*
ID: daniel25
TASK: skidesign
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	// reading input
	// ifstream reader("input.txt");
	ifstream reader("skidesign.in");
	string line;
	int numHills;
	vector<int> hillHeights;
	if (reader.is_open()) {
		getline(reader, line);
		numHills = stoi(line);
		for (int i = 0; i < numHills; i++) {
			getline(reader, line);
			hillHeights.push_back(stoi(line));
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();


	int minCost = 100000000;
	for (int i = 1; i <= 83; i++) {
		int cost = 0;
		for (int j = 0; j < hillHeights.size(); j++) {
			if (hillHeights[j] > i && hillHeights[j] < i + 17) {
				continue;
			} else if (hillHeights[j] > i + 17) {
				cost += (hillHeights[j] - (i + 17)) * (hillHeights[j] - (i + 17));
			} else if (hillHeights[j] < i) {
				cost += (i - hillHeights[j]) * (i - hillHeights[j]);
			}
		}
		minCost = min(minCost, cost);
	}

	// writing output
	// ofstream writer("output.txt");
	ofstream writer("skidesign.out");
	if (writer.is_open()) {
		writer << minCost << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
}