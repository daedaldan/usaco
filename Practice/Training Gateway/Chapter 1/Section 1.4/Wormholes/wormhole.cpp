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

int N = 0;
vector<int> X, Y, partner, next_on_right;

bool isCycle() {
	for (int start = 1; start <= N; start++) {
		int pos = start;
		for (int count = 0; count < N; count++)
			pos = next_on_right[partner[pos]];
		if (pos != 0)
			return true;
	}

	return false;
}

int solve() {
	int i = 0;
	int total = 0;

	for (i = 1; i <= N; i++)
		if (partner[i] == 0) break;

	if (i > N) {
		if (isCycle())
			return 1;
		else
			return 0;
	}

	for (int j = i+1; j <= N; j++) {
		if (partner[j] == 0)  {
			partner[i] = j;
			partner[j] = i;
			total += solve();
			partner[i] = 0;
			partner[j] = 0;
		}
	}

	return total;
}

int main() {
	for (int i = 0; i < 13; i++) {
		X.push_back(0);
		Y.push_back(0);
		partner.push_back(0);
		next_on_right.push_back(0);
	}

	// reading input
	// ifstream reader("input.txt");
	ifstream reader("wormhole.in");
	string line;
	if (reader.is_open()) {
		getline(reader, line);
		N = stoi(line);
		for (int i = 1; i <= N; i++) {
			getline(reader, line);
			X[i] = stoi(line.substr(0, line.find(" ")));
			Y[i] = stoi(line.substr(line.find(" ")));
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (X[j] > X[i] && Y[j] == Y[i]) {
				if (next_on_right[i] == 0 ||
					X[j] - X[i] < X[next_on_right[i]] - X[i])
					next_on_right[i] = j;
			}
		}
	}

	// writing output
	// ofstream writer("output.txt");
	ofstream writer("wormhole.out");
	if (writer.is_open()) {
		writer << solve() << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}