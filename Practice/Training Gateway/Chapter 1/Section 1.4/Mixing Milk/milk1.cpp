/*
ID: daniel25
TASK: milk
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
	ifstream reader("milk.in");
	string mmmInfo;
	int milkNeed = -1;
	int numFarmers = -1;
	string strFarmerInfo;
	// 2D vector with unit price and quantity of milk from farmers
	vector<vector<int>> farmers;
	if (reader.is_open()) {
		getline(reader, mmmInfo);
		milkNeed = stoi(mmmInfo.substr(0, mmmInfo.find(" ")));
		numFarmers = stoi(mmmInfo.substr(mmmInfo.find(" ")));
		for (int i = 0; i < numFarmers; i++) {
			getline(reader, strFarmerInfo);
			vector<int> farmerInfo;
			farmerInfo.push_back(stoi(strFarmerInfo.substr(0, strFarmerInfo.find(" "))));
			farmerInfo.push_back(stoi(strFarmerInfo.substr(strFarmerInfo.find(" "))));
			farmers.push_back(farmerInfo);
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	int minCost = 0;
	int milkBought = 0;

	// sorting vector of farmer info in increasing order of unit price
	sort(farmers.begin(), farmers.end(), [](vector<int> & a, vector<int> & b) {
		return a[0] < b[0];
	});

	for (int i = 0; i < farmers.size(); i++) {
		while (farmers[i][1] > 0 && milkBought < milkNeed) {
			milkBought += 1;
			farmers[i][1] -= 1;
			minCost += farmers[i][0];
		}
	}

	// ofstream writer("output.txt");
	ofstream writer("milk.out");
	if (writer.is_open()) {
		writer << minCost << "\n";
	} else {
		cout << "error opening file" << endl;
	}

	return 0;
}