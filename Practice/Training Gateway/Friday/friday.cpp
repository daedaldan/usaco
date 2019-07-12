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
			thirteenths[daysToWeekday(days + 63, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 94, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 124, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 155, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 175, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 206, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 237, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 267, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 298, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 328, weekdayKey)] += 1;
			days += 366;
		} else {
			thirteenths[daysToWeekday(days + 13, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 44, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 62, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 93, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 123, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 154, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 174, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 205, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 236, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 266, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 297, weekdayKey)] += 1;
			thirteenths[daysToWeekday(days + 327, weekdayKey)] += 1;
			days += 365;
		}
	}

	cout << "Mon: " << thirteenths["Mon"] << " ";
	cout << "Tue: " << thirteenths["Tue"] << " ";
	cout << "Wed: " << thirteenths["Wed"] << " ";
	cout << "Thu: " << thirteenths["Thu"] << " ";
	cout << "Fri: " << thirteenths["Fri"] << " ";
	cout << "Sat: " << thirteenths["Sat"] << " ";
	cout << "Sun: " << thirteenths["Sun"] << " ";

	ofstream writer("output.txt");
	if (writer.is_open()) {

	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();
	
	return 0;
}