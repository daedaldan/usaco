#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct bucket {
	int milk;
	int size;
};

void pour(bucket & a, bucket & b) {
	while (a.milk != 0 && b.milk < b.size) {
		b.milk += 1;
		a.milk -= 1;
	}
}

int main() {
	// reading input
	ifstream reader("mixmilk.in");
	vector<string> inputData;
	string inputLine;
	if (reader.is_open()) {
		while (getline(reader, inputLine))
			inputData.push_back(inputLine);
	} else {
		cout << "error opening input file" << endl;
	}

	reader.close();

	// putting input into variables
	bucket a;
	a.size = stoi(inputData[0].substr(0,inputData[0].find(" ")));
	a.milk = stoi(inputData[0].substr(inputData[0].find(" "), inputData[0].length()));
	bucket b;
	b.size = stoi(inputData[1].substr(0,inputData[1].find(" ")));
	b.milk = stoi(inputData[1].substr(inputData[1].find(" "), inputData[1].length()));
	bucket c;
	c.size = stoi(inputData[2].substr(0,inputData[2].find(" ")));
	c.milk = stoi(inputData[2].substr(inputData[2].find(" "), inputData[2].length()));

	// simulating pour operations
	int pours = 0;
	int last = 1;
	while (pours < 100) {
		if (last == 1) {
			pour(a, b);
			last = 2;
		} else if (last == 2) {
			pour(b, c);
			last = 3;
		} else if (last == 3) {
			pour(c, a);
			last = 1;
		}

		pours += 1;
	}

	// writing output
	ofstream writer("mixmilk.out");
	if (writer.is_open()) {
		writer << a.milk << "\n";
		writer << b.milk << "\n";
		writer << c.milk << "\n";
	} else {
		cout << "error opening output file" << endl;
	}

	writer.close();

	return 0;
}