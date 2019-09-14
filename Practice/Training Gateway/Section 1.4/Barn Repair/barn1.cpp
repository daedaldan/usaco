/*
ID: daniel25
TASK: barn1
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
	ifstream reader("input.txt");
	// ifstream reader("barn1.in");
	string backgroundInfo;
	string cowPos;
	int maxBoards = -1;
	int numStalls = -1;
	int numCows = -1;
	vector<int> occupStalls;
	if (reader.is_open()) {
		getline(reader, backgroundInfo);
		int firstSpace = backgroundInfo.find(" ");
		int secondSpace = backgroundInfo.find(" ", firstSpace+1);
		maxBoards = stoi(backgroundInfo.substr(0, firstSpace));
		numStalls = stoi(backgroundInfo.substr(firstSpace, secondSpace));
		numCows = stoi(backgroundInfo.substr(secondSpace));
		for (int i = 0; i < numCows; i++) {
			getline(reader, cowPos);
			occupStalls.push_back(stoi(cowPos));
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	// base case
	if (maxBoards > numCows) {
		ofstream writer("output.txt");
		// ofstream writer("barn1.out");
		if (writer.is_open()) {
			writer << numCows << "\n";
		} else {
			cout << "error opening output file" << endl;
		}
		writer.close();
	} else {
		// initializing vector of booleans representing stalls with boards
		int boardsUsed = 0;
		vector<bool> boardedStalls;
		for (int i = 0; i < numStalls; i++)
			boardedStalls.push_back(false);

		int firstCow = *min_element(occupStalls.begin(), occupStalls.end());
		int lastCow = *max_element(occupStalls.begin(), occupStalls.end());

		// putting in the initial board
		for (int i = firstCow-1; i < lastCow; i++)
			boardedStalls[i] = true;
		boardsUsed += 1;

		// greedy algorithm
		while(boardsUsed < maxBoards) {
			int longestEmpty = -1;
			int leStart = -1;
			int leEnd = -1;
			for (int i = 0; i < boardedStalls.size(); i++) {
				if (boardedStalls[i] && find(occupStalls.begin(), occupStalls.end(), i+1) == occupStalls.end()) {
					int start = i;
					int end = i;
					int length = 1;
					i += 1;
					while(boardedStalls[i] && find(occupStalls.begin(), occupStalls.end(), i+1) == occupStalls.end()) {
						end += 1;
						i += 1;
					}
					if ((end + 1 - start) > longestEmpty) {
						leStart = start;
						leEnd = end;
						longestEmpty = end + 1 - start;
					}
					i -= 1;
				}
			}
			for (int i = leStart; i <= leEnd; i++) {
				boardedStalls[i] = false;
			}

			boardsUsed += 1;
		}

		// computing number of covered stalls
		int coveredStalls = 0;

		for (int i = 0; i < boardedStalls.size(); i++) {
			if (boardedStalls[i])
				coveredStalls += 1;
		}

		// writing output
		ofstream writer("output.txt");
		// ofstream writer("barn1.out");
		if (writer.is_open()) {
			writer << coveredStalls << "\n";
		} else {
			cout << "error opening output file" << endl;
		}
		writer.close();
	}

	return 0;
}