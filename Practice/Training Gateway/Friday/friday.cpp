/*
ID: daniel25
TASK: friday
LANG: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

// input: days from beginning of 1900; output: weekday of that day
string daysToWeekday(int n) {
	
}

int yearsToDays(int n) {
	int days = 0;
	for (int i = 1900; i < 1900 + n; i++) {
		if (i == 2000 || ((i % 4 == 0) && (i % 100 != 0))) {
			days += 366;
		} else {
			days += 365;
		}
	}

	return days;
}


int main() {
	ifstream reader("input.txt");
	int years = -1;
	string yearsStr = "yearsStr";
	if (reader.is_open()) {
		getline(reader, yearsStr);
		years = stoi(yearsStr);
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	// map of weekday to number of 13ths on that weekday throughout given years
	map<string, int> thirteenths;
	thirteenths["Mon"] = 0;
	thirteenths["Tue"] = 0;
	thirteenths["Wed"] = 0;
	thirteenths["Thu"] = 0;
	thirteenths["Fri"] = 0;
	thirteenths["Sat"] = 0;
	thirteenths["Sun"] = 0;
	cout << thirteenths["Mon"] << endl;

	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
	
	return 0;
}