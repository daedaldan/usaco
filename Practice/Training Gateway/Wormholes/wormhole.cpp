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

bool operator==(const wormhole & wh1, const wormhole & wh2) {return wh1.id == wh2.id;}

bool noExistingPair(vector<vector<vector<int>>> & pairSets, vector<int> p) {
	for (int i = 0; i < pairSets.size(); i++) {
		for (int j = 0; j < pairSets[i].size(); j++) {
			if ((pairSets[i][j][0] == p[0] && pairSets[i][j][1] == p[1]) || (pairSets[i][j][0] == p[1] && pairSets[i][j][1] == p[0]))
				return false;
		}
	}
	

	return true;
}

void generateUniquePairs(vector<vector<vector<int>>> & pairSets, vector<vector<int>> & pairs, vector<int> remaining, vector<int> pair) {
	if (pair.size() == 2) {
		// cout << "here" << endl;
		// cout << pair[0] << " " << pair[1] << endl;
		if (noExistingPair(pairSets, pair)) {
			// cout << "made it" << endl;
			pairs.push_back(pair);
		}
	} else {
		for (int i = 0; i < remaining.size(); i++) {
			for (int j = 0; j < remaining.size(); j++) {
				// cout << remaining[i] << " " << remaining[j] << endl;
				// cout << "    " << i << " " << j << endl;
				if (i != j) {
					// cout << "here" << endl;
					pair.push_back(remaining[i]);
					pair.push_back(remaining[j]);
					if (noExistingPair(pairSets, pair)) {
						remaining.erase(remaining.begin() + i);
						if (i < j)
							remaining.erase(remaining.begin() + j - 1);
						else
							remaining.erase(remaining.begin() + j);
					}	
					generateUniquePairs(pairSets, pairs, remaining, pair);
					pair.clear();
				}
			}	
		}
	}	
}

bool isCycle(vector<int> & starting, vector<int> current, vector<vector<int>> & pairs, vector<wormhole> & holes, bool & start, int & count) {
	count += 1;
	if (count > 100000000)
		return false;
	if (((starting[0] == current[0] && starting[1] == current[1]) || (starting[0] == current[1] && starting[1] == current[0])) && !start) {
		// cout << "here" << endl;
		return true;
		// cout << "true" << endl;
	}
	// cout << "here" << endl;
	start = false;
	for (int i = 0; i < pairs.size(); i++) {
		for (int cur = 0; cur <= 2; cur++) {
			for (int next = 0; next <= 2; next++) {
				// cout << "current: " << (holes[current[cur]]).x << " " << (holes[current[cur]]).y << endl;
				if ((holes[current[cur]]).x < (holes[pairs[i][next]]).x && (holes[current[cur]]).y == (holes[pairs[i][next]]).y) {
					return isCycle(starting, pairs[i], pairs, holes, start, count);
				}
			}
		}
	}
	// cout << "false" << endl;
	return false;
}


int main() {
	// reading input
	ifstream reader("input.txt");
	// ifstream reader("wormhole.in");
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

	vector<int> ids;
	for (int i = 0; i < wormholes.size(); i++)
		ids.push_back(wormholes[i].id);

	vector<vector<vector<int>>> pairSets;
	vector<int> emptyPair;
	while (pairSets.size() < (wormholes.size() * (wormholes.size() - 1)) / 4) {
		vector<vector<int>> pairs;
		generateUniquePairs(pairSets, pairs, ids, emptyPair);
		pairSets.push_back(pairs);
	}
	

	// cout << pairSets.size() << endl;

	// calculate set of unique pairings of wormholes
	// for (int i = 0; i < pairSets.size(); i++) {
	// 	cout << "Set: " << i + 1 << endl;
 // 		for (int j = 0; j < pairSets[i].size(); j++) {
	// 		cout << "    " << pairSets[i][j][0] << " " << pairSets[i][j][1] << endl;
	// 	}
	// }


	vector<int> empPair;
	empPair.push_back(1001);
	empPair.push_back(1001);
	bool start = true;
	int count = 0;
// cout << "here" << endl;
	int cycles = 0;
	for (int i = 0; i < pairSets.size(); i++) {
		// cout << "yo wassup" << endl;
		for (int j = 0; j < pairSets[i].size(); j++) {
			// cout << "j: " << j << endl;
			// cout << "set: " << i + 1 << endl;
			cout << cycles << endl;
			if (isCycle(pairSets[i][j], empPair, pairSets[i], wormholes, start, count)) {
				// cout << "made it" << endl;
				cycles += 1;
			}
		}

	}

	cout << cycles << endl;

	// writing output
	ofstream writer("output.txt");
	// ofstream writer("wormhole.out");
	if (writer.is_open()) {
		cout << "made it to output" << endl;
		writer << cycles << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}