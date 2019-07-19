/*
ID: daniel25
TASK: wormhole
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
		return false;

	return true;
}

void calculateWormholePairs(vector<wormhole> & holes, vector<holePair> soFar, vector<vector<holePair>> & pairs) {
	if (soFar.size() == (holes.size() / 2)) {
		cout << "here " << endl;
		pairs.push_back(soFar);
	}
	
	for (int i = 0; i < holes.size(); i++) {
		for (int j = 0; j < holes.size(); j++) {
			holePair p;
			p.id1 = holes[i].id;
			p.id2 = holes[j].id;
			bool valid = true;
			for (int k = 0; k < soFar.size(); k++) {
				if (duplicateHoles(p, soFar[k])) {
					valid = false;
					break;
				}
			}
			if (valid) {
				soFar.push_back(p);
			}
			calculateWormholePairs(holes, soFar, pairs);
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
	// mark starting hole
	// set current hole to starting hole
	// if hole with same y value and greater x value, set current hole to that hole
	// if that hole is the starting hole, there is a cycle
	// repeat

	// writing output
	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}