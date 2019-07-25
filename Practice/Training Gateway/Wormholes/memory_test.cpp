/*
ID: daniel25
TASK: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
	vector<int> testV;
	// vector<int> empty;
	// empty.push_back(0);
	// empty.push_back(0);

	for (int i = 0; i <= 1050000; i++) {
		testV.push_back(0);
		if (i % 100000 == 0 && i < 1048500)
			cout << i << endl;
		if (i >= 1048500)
			cout << i << endl;
	}

	ofstream fout("wormhole.out");
	fout.close();
}