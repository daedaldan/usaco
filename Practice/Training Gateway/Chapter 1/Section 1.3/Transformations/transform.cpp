/*
ID: daniel25
TASK: transform
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

bool equalSquare(vector<vector<char>> & a, vector<vector<char>> & b) {
	if (a.size() != b.size())
		cout << "sizes don't match" << endl;
	if (a.size() != a[0].size())
		cout << "not a square" << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			if (a[i][j] == b[i][j]) {
				continue;
			} else {
				return false;
			}
		}
	}

	return true;
}

vector<vector<char>> rotateNinety(vector<vector<char>> sqr) {
	// initializing output square
	vector<vector<char>> newSqr;
	for (int i = 0; i <sqr.size(); i++) {
		vector<char> line;
		for (int j = 0; j < sqr.size(); j++) {
			line.push_back('X');
		}
		newSqr.push_back(line);
	}
	// scenario 1: square length is odd
	if (sqr.size() % 2 == 1) {
		int bound = floor(sqr.size() / 2);
		for (int i = -bound; i <= bound; i++) {
			for (int j = -bound; j <= bound; j++) {
				newSqr[j+bound][-i+bound] = sqr[i+bound][j+bound];
			}
		}
	} // scenario 2: square length is even
	else {
		int bound = sqr.size() / 2;
		for (int i = 0; i < sqr.size(); i++) {
			for (int j = 0; j < sqr.size(); j++) {
				newSqr[j][-i+sqr.size()-1] = sqr[i][j];
			}	
		}
	}

	return newSqr;
}

vector<vector<char>> rotateOneEighty(vector<vector<char>> sqr) {
	// initializing output square
	vector<vector<char>> newSqr;
	for (int i = 0; i <sqr.size(); i++) {
		vector<char> line;
		for (int j = 0; j < sqr.size(); j++) {
			line.push_back('X');
		}
		newSqr.push_back(line);
	}
	// scenario 1: square length is odd
	if (sqr.size() % 2 == 1) {
		int bound = floor(sqr.size() / 2);
		for (int i = -bound; i <= bound; i++) {
			for (int j = -bound; j <= bound; j++) {
				newSqr[-i+bound][-j+bound] = sqr[i+bound][j+bound];
			}
		}
	} // scenario 2: square length is even
	else {
		int bound = sqr.size() / 2;
		for (int i = 0; i < sqr.size(); i++) {
			for (int j = 0; j < sqr.size(); j++) {
				newSqr[-i+sqr.size()-1][-j+sqr.size()-1] = sqr[i][j];
			}	
		}
	}

	return newSqr;
}

vector<vector<char>> rotateTwoSeventy(vector<vector<char>> sqr) {
	// initializing output square
	vector<vector<char>> newSqr;
	for (int i = 0; i <sqr.size(); i++) {
		vector<char> line;
		for (int j = 0; j < sqr.size(); j++) {
			line.push_back('X');
		}
		newSqr.push_back(line);
	}
	// scenario 1: square length is odd
	if (sqr.size() % 2 == 1) {
		int bound = floor(sqr.size() / 2);
		for (int i = -bound; i <= bound; i++) {
			for (int j = -bound; j <= bound; j++) {
				newSqr[-j+bound][i+bound] = sqr[i+bound][j+bound];
			}
		}
	} // scenario 2: square length is even
	else {
		int bound = sqr.size() / 2;
		for (int i = 0; i < sqr.size(); i++) {
			for (int j = 0; j < sqr.size(); j++) {
				newSqr[-j+sqr.size()-1][i] = sqr[i][j];
			}	
		}
	}

	return newSqr;
}

vector<vector<char>> reflectHoriz(vector<vector<char>> sqr) {
	// initializing output square
	vector<vector<char>> newSqr;
	for (int i = 0; i <sqr.size(); i++) {
		vector<char> line;
		for (int j = 0; j < sqr.size(); j++) {
			line.push_back('X');
		}
		newSqr.push_back(line);
	}
	// scenario 1: square length is odd
	if (sqr.size() % 2 == 1) {
		int bound = floor(sqr.size() / 2);
		for (int i = -bound; i <= bound; i++) {
			for (int j = -bound; j <= bound; j++) {
				newSqr[i+bound][-j+bound] = sqr[i+bound][j+bound];
			}
		}
	} // scenario 2: square length is even
	else {
		int bound = sqr.size() / 2;
		for (int i = 0; i < sqr.size(); i++) {
			for (int j = 0; j < sqr.size(); j++) {
				if (i > 0)
					newSqr[i][-j+sqr.size()-1] = sqr[i][j];
				else
					newSqr[i][-j+sqr.size()-1] = sqr[i][j];
			}	
		}
	}

	return newSqr;
}

int main() {
	// reading input
	// ifstream reader("input.txt");
	ifstream reader("transform.in");
	int sizeSquare = -1;
	string strSizeSquare;
	// 2D vectors storing contents of input squares
	vector<vector<char>> origSquare;
	vector<vector<char>> transformSquare;
	if (reader.is_open()) {
		getline(reader, strSizeSquare);
		sizeSquare = stoi(strSizeSquare);
		// reading original square
		for (int i = 0; i < sizeSquare; i++) {
			string strLine;
			vector<char> line;
			getline(reader, strLine);
			for (int j = 0; j < sizeSquare; j++) {
				line.push_back(strLine[j]);
			}
			origSquare.push_back(line);
		}
		// reading transformed square
		for (int i = 0; i < sizeSquare; i++) {
			string strLine;
			vector<char> line;
			getline(reader, strLine);
			for (int j = 0; j < sizeSquare; j++) {
				line.push_back(strLine[j]);
			}
			transformSquare.push_back(line);
		}
	} else {
		cout << "error opening input file" << endl;
	}
	reader.close();

	// printing original square to console
	cout << "Original Square:" << endl;
	for (int i = 0; i < sizeSquare; i++) {
		for (int j = 0; j < sizeSquare; j++) {
			cout << origSquare[i][j];
		}
		cout << endl;
	}
	cout << endl;

	// TEST: printing transformed original square to console
	// cout << "Transformed Original Square:" << endl;
	// origSquare = rotateTwoSeventy(origSquare);
	// for (int i = 0; i < sizeSquare; i++) {
	// 	for (int j = 0; j < sizeSquare; j++) {
	// 		cout << origSquare[i][j];
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	// printing transformed square to console
	cout << "Transformed Square:" << endl;
	for (int i = 0; i < sizeSquare; i++) {
		for (int j = 0; j < sizeSquare; j++) {
			cout << transformSquare[i][j];
		}
		cout << endl;
	}
	cout << endl;

	// each case value represents a specific scenario e.g. case 1 is 90 degree rotation
	int transformCase = -1;

	vector<vector<char>> rotatedNinety = rotateNinety(origSquare);
	vector<vector<char>> rotatedOneEighty = rotateOneEighty(origSquare);
	vector<vector<char>> rotatedTwoSeventy = rotateTwoSeventy(origSquare);
	vector<vector<char>> reflectedHoriz = reflectHoriz(origSquare);

	// checking each case to find a match
	if(equalSquare(transformSquare, rotatedNinety)) {
		transformCase = 1;
	} else if(equalSquare(transformSquare, rotatedOneEighty)) {
		transformCase = 2;
	} else if(equalSquare(transformSquare, rotatedTwoSeventy)) {
		transformCase = 3;
	} else if(equalSquare(transformSquare, reflectedHoriz)) {
		transformCase = 4;
	} else {
		vector<vector<char>> combRotatedNinety = rotateNinety(reflectedHoriz);
		vector<vector<char>> combRotatedOneEighty = rotateOneEighty(reflectedHoriz);
		vector<vector<char>> combRotatedTwoSeventy = rotateTwoSeventy(reflectedHoriz);
		if(equalSquare(transformSquare, combRotatedNinety)) {
			transformCase = 5;
		} else if(equalSquare(transformSquare, combRotatedOneEighty)) {
			transformCase = 5;
		} else if(equalSquare(transformSquare, combRotatedTwoSeventy)) {
			transformCase = 5;
		} else if (equalSquare(origSquare, transformSquare)) {
			transformCase = 6;
		} else {
			transformCase = 7;
	 	}
	} 

	// ofstream writer("output.txt");
	ofstream writer("transform.out");
	if (writer.is_open()) {
		writer << transformCase << "\n";
	} else {
		cout << "error opening output file" << endl;
	}
	writer.close();

	return 0;
}