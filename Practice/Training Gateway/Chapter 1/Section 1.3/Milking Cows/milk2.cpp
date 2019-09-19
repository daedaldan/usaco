/*
ID: daniel25
TASK: milk2
LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream reader("milk2.in");
	// ifstream reader("input.txt");
	int numFarmers = -1;
	string strNumFarmers;
	string milkStartEnd;
	vector<vector<int>> startEndTimes;
	if (reader.is_open()) {
		getline(reader, strNumFarmers);
		numFarmers = stoi(strNumFarmers);
		// storing input start and end times in 2D vector, each element containing two integers (start and end times)
		for (int i = 0; i < numFarmers; i++) {
			getline(reader, milkStartEnd);
			vector<int> startEnd;
			startEnd.push_back(stoi(milkStartEnd.substr(0, milkStartEnd.find(" "))));
			startEnd.push_back(stoi(milkStartEnd.substr(milkStartEnd.find(" "), milkStartEnd.length())));
			startEndTimes.push_back(startEnd);
		}
	} else {
		cout << "error opening input file" << endl;
	}

	// 1D vector; true slots represent milking occurring at that time, false slots represent idleness
	vector<int> activityLine;

	for (int i = 0; i < startEndTimes.size(); i++) {
		if (startEndTimes[i][1] > activityLine.size()) {
			while (activityLine.size() < startEndTimes[i][1]) {
				activityLine.push_back(false); 
			}
		}

		for (int j = startEndTimes[i][0]; j < startEndTimes[i][1]; j++)
			activityLine[j] = true;
	}

	int maxActivity = 0;
	int maxIdle = 0;

	int start = 0;
	while (!activityLine[start]) {
		start += 1;
	}

	// cout << start << endl;

	// visual representation of activity line
	// for (int i = start; i < activityLine.size(); i++) {
	// 	if (activityLine[i]) {
	// 		cout << "X";
	// 	} else {
	// 		cout << "O";
	// 	}
	// }
	// cout << endl;

	for (int i = start; i < activityLine.size(); i++) {
		if (activityLine[i]) {
			int active = 0;
			while (activityLine[i]) {
				active += 1;
				i++;
			}
			if (active > maxActivity) {
				maxActivity = active;
			}
			i -= 1;
		} else {
			int idle = 0;
			while (!activityLine[i]) {
				idle += 1;
				i++;
			}
			if (idle > maxIdle) {
				maxIdle = idle;
			}
			i -= 1;
		}
	}

	ofstream writer("milk2.out");
	// ofstream writer("output.txt");
	if (writer.is_open()) {
		writer << maxActivity << " " << maxIdle << "\n";
	} else {
		cout << "error opening output file" << endl;
	}

	return 0;
}
