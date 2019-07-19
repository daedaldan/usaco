/*
ID: daniel25
TASK: skidesign
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	// reading input
	ifstream reader("input.txt");
	// ifstream reader("skidesign.in");
	string line;
	int numHills;
	multiset<int> hillHeights;
	if (reader.is_open()) {
		getline(reader, line);
		numHills = stoi(line);
		for (int i = 0; i < numHills; i++) {
			getline(reader, line);
			hillHeights.insert(stoi(line));
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();
	

	int max = *hillHeights.rbegin();
	int min = *hillHeights.begin();
	int cost = 0;
	int count = 0;
	while (max - min > 17) {
		int needed = ceil((max - min - 17) / 2.0);
		cost += 2 * (needed * needed);

		hillHeights.erase(hillHeights.begin(), ++hillHeights.begin());
		hillHeights.erase(--hillHeights.end(), hillHeights.end());
		hillHeights.insert(max - needed);
		hillHeights.insert(min + needed);

		max = *hillHeights.rbegin();
		min = *hillHeights.begin();
		cout << hillHeights.size() << endl;
	}

	// writing output
	ofstream writer("output.txt");
	// ofstream writer("skidesign.out");
	if (writer.is_open()) {
		writer << cost << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
}