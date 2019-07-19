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

int indexOf(int i, vector<int> v) {
	vector<int>::iterator it = find(v.begin(), v.end(), i);
	if (it == v.end()) {
		return -1;
	} else {
		return distance(v.begin(), it);
	}
}

int findMax(vector<int> v) {
	int max = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > max)
			max = v[i];
	}

	return max;
}

int findMin(vector<int> v) {
	int min = 1001;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < min)
			min = v[i];
	}
	
	return min;	
}

int main() {
	// reading input
	ifstream reader("input.txt");
	// ifstream reader("skidesign.in");
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
	

	int max = *max_element(hillHeights.begin(), hillHeights.end());
	int min = *min_element(hillHeights.begin(), hillHeights.end());
	int cost = 0;
	while (max - min > 17) {
		int needed = (max - min - 17) / 2;
		cost += 2 * (needed * needed);

		hillHeights[indexOf(max, hillHeights)] -= needed;
		hillHeights[indexOf(min, hillHeights)] += needed;

		max = *max_element(hillHeights.begin(), hillHeights.end());
		min = *min_element(hillHeights.begin(), hillHeights.end());
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