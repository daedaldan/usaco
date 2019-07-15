/*
ID: daniel25
TASK: namenum
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

void populateTouchTone(map<char, vector<string>> & tt) {
	vector<string> two;
	two.push_back("A");
	two.push_back("B");
	two.push_back("C");
	tt.insert({'2', two});
	vector<string> three;
	three.push_back("D");
	three.push_back("E");
	three.push_back("F");
	tt.insert({'3', three});
	vector<string> four;
	four.push_back("G");
	four.push_back("H");
	four.push_back("I");
	tt.insert({'4', four});
	vector<string> five;
	five.push_back("J");
	five.push_back("K");
	five.push_back("L");
	tt.insert({'5', five});
	vector<string> six;
	six.push_back("M");
	six.push_back("N");
	six.push_back("O");
	tt.insert({'6', six});
	vector<string> seven;
	seven.push_back("P");
	seven.push_back("R");
	seven.push_back("S");
	tt.insert({'7', seven});
	vector<string> eight;
	eight.push_back("T");
	eight.push_back("U");
	eight.push_back("V");
	tt.insert({'8', eight});
	vector<string> nine;
	nine.push_back("W");
	nine.push_back("X");
	nine.push_back("Y");
	tt.insert({'9', nine});
}

void createPossibleNames(map<char, vector<string>> & tt, vector<string> & names, string used, string remaining) {
	if (remaining.size() == 1) {
		names.push_back(used + tt[remaining[0]][0]);
		names.push_back(used + tt[remaining[0]][1]);
		names.push_back(used + tt[remaining[0]][2]);
		return;
	}
	if (used[0] == 'H')
		cout << "used: " << used << " remaining: " << remaining << endl;
	for (int i = 0; i < 3; i++) {
		createPossibleNames(tt, names, used + tt[remaining[0]][i], remaining.substr(1));
	}
}

int main() {
	// reading input 
	// ifstream reader("input.txt");
	ifstream reader("namenum.in");
	string cowNum;
	if (reader.is_open()) {
		getline(reader, cowNum);
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();
	reader.clear();

	// reading names from dictionary of valid names
	unordered_map<string, string> dict;
	string validName;
	reader.open("dict.txt");
	if (reader.is_open()) {
		while (getline(reader, validName)) 
			dict[validName] = validName;
	} else {
		cout << "error opening dictionary file" << endl;
	}
	reader.close();

	// initializing map of TouchTone keys
	map<char, vector<string>> touchTone;
	populateTouchTone(touchTone);

	// creating vector of possible cow names based on number given
	vector<string> possibleNames;
	createPossibleNames(touchTone, possibleNames, "", cowNum);

	// creating vector of valid cow names based on dict
	vector<string> validNames;

	for (int i = 0; i < possibleNames.size(); i++) {
		if (dict.find(possibleNames[i]) != dict.end())
			validNames.push_back(possibleNames[i]);
	}

	possibleNames.shrink_to_fit();

	// writing output 
	// ofstream writer("output.txt");
	ofstream writer("namenum.out");
	if (writer.is_open()) {
		if (validNames.size() > 0) {
			for (int i = 0; i < validNames.size(); i++) {
				writer << validNames[i] << "\n";
			}
		} else {
			writer << "NONE\n";
		}
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}