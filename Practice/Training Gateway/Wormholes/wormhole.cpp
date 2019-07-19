/*
ID: daniel25
TASK: wormhole
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct wormhole {
	int x;
	int y;
	int id;
};

struct holePair {
	int id1;
	int id2;
};

// returns true if input holePairs contain duplicate wormholes
bool duplicateHoles(holePair a, holePair b) {
	if (a.id1 == b.id1 || a.id2 == b.id2)
		return false;
	if (a.id2 == b.id1 || a.id1 == b.id2)
		return false;

	return true;
}

void calculateWormholePairs(vector<wormhole> holes, vector<holePair> soFar, vector<vector<holePair>> & pairs) {
		if (holes.size() == 0) {
		pairs.push_back(soFar);
	} else {
		for (int i = 0; i < holes.size(); i++) {
			for (int j = 0; j < holes.size(); j++) {
				holePair p;
				p.id1 = holes[i].id;
				p.id2 = holes[j].id;
				if (holes[i].id != holes[j].id && find(soFar.begin(), soFar.end(), p) == soFar.end()) {
					soFar.push_back(p);
					vector<wormhole> newHoles = holes;
					newHoles.erase(find(holes.begin(), holes.end(), holes[i]), ++find(holes.begin(), holes.end(), holes[i]));
					newHoles.erase(find(holes.begin(), holes.end(), holes[j]), ++find(holes.begin(), holes.end(), holes[j]));
					calculateWormholePairs(newHoles, soFar, pairs);
				}
			}
		}
	}
}

// bool isCycle()

int main() {
	// reading input
	ifstream reader("input.txt");
	string line;
	int numHoles;
	vector<wormhole> wormholes;
	if (reader.is_open()) {
		getline(reader, line);
		numHoles = stoi(line);
		for (int i = 0; i < numHoles; i++) {
			getline(reader, line);
			wormhole hole;
			hole.x = stoi(line.substr(0, line.find(" ")));
			hole.y = stoi(line.substr(line.find(" ")));
			hole.id = i;
			wormholes.push_back(hole);
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();


	// calculate set of unique holePairs
	vector<vector<holePair>> wormholePairs;
	vector<holePair> emptyholePairs;

	calculateWormholePairs(wormholes, emptyholePairs, wormholePairs);
	cout << wormholePairs.size() << endl;
	for (int i = 0; i < wormholePairs.size(); i++) {
		for (int j = 0; j < wormholePairs[i].size(); j++) {
			int start = wormholePairs[i][j][0];
			int current = start;
			for (int k = 0)
		}
	}

	// writing output
	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}