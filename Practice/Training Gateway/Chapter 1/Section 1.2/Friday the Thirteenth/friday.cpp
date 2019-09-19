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
string daysToWeekday(int n, map<int, string> key) {
	return key[(n % 7)];
}


int main() {
	ifstream reader("friday.in");
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

	// key returning weekday based on days from beginning of 1900 % 7
	map<int, string> weekdayKey;
	weekdayKey[0] = "Sun";
	weekdayKey[1] = "Mon";
	weekdayKey[2] = "Tue";
	weekdayKey[3] = "Wed";
	weekdayKey[4] = "Thu";
	weekdayKey[5] = "Fri";
	weekdayKey[6] = "Sat";

	int days = 0;
	for (int i = 1900; i < 1900 + years; i++) {
		if (i == 2000 || ((i % 4 == 0) && (i % 100 != 0))) {
			thirteenths[daysToWeekday(days + 13, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 44, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 73, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 104, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 134, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 165, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 195, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 226, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 257, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 287, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 318, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 348, weekdayKey)] += 1;
			days += 366;
		} else {
			thirteenths[daysToWeekday(days + 13, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 44, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 72, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 103, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 133, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 164, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 194, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 225, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 256, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 286, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 317, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 347, weekdayKey)] += 1;
			days += 365;
		}
	}

	// cout << "Sat: " << thirteenths["Sat"] << " ";
	// cout << "Sun: " << thirteenths["Sun"] << " ";
	// cout << "Mon: " << thirteenths["Mon"] << " ";
	// cout << "Tue: " << thirteenths["Tue"] << " ";
	// cout << "Wed: " << thirteenths["Wed"] << " ";
	// cout << "Thu: " << thirteenths["Thu"] << " ";
	// cout << "Fri: " << thirteenths["Fri"] << " ";
	// correct answer: 36 33 34 33 35 35 34

	ofstream writer("friday.out");
	if (writer.is_open()) {
		writer << thirteenths["Sat"] << " " << thirteenths["Sun"] << " " << thirteenths["Mon"] << " " << thirteenths["Tue"] << " " << thirteenths["Wed"] << " " << thirteenths["Thu"] << " " << thirteenths["Fri"] << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
	
	return 0;
}