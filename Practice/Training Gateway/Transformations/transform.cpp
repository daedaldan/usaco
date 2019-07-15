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
		// int bound = sqr.size() / 2;
		// for (int i = -bound; i <= bound; i++) {
		// 	if (i != 0) {
		// 		cout << "i: " << i << " ";
		// 		for (int j = -bound; j <= bound; j++) {
		// 			if (j != 0) {
		// 				cout << "j: " << j << endl;
		// 				int newI = -10;
		// 				int newJ = -10;
		// 				// if (i < 0)
		// 				// 	newI = i + bound;
		// 				// else
		// 				// 	newI = i + bound - 1;
		// 				// if (j < 0)
		// 				// 	newJ = j + bound;
		// 				// else
		// 				// 	newJ = j + bound - 1;
		// 				// cout << "newI: " << newI << " " << "newJ: " << newJ << endl;
		// 				if (i < 0 && j < 0) {
		// 					newSqr[j + bound][-i + bound] = sqr[i + bound][j + bound];
		// 				} else if (i > 0 && j > 0) {
		// 					newSqr[newJ = j + bound - 1][-i + bound - 1] = sqr[i + bound - 1][newJ = j + bound - 1];
		// 				} else if (i < 0 && j > 0) {
		// 					newSqr[newJ = j + bound - 1][-i + bound] = sqr[i + bound][newJ = j + bound - 1];
		// 				} else if (i > 0 && j < 0){
		// 					newSqr[j + bound][-i + bound - 1] = sqr[i + bound - 1][j + bound];
		// 				}
		// 			}
		// 		}
		// 	}
		// }
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
	// origSquare = rotateNinety(origSquare);
	cout << "Transformed Original Square:" << endl;
	for (int i = 0; i < sizeSquare; i++) {
		for (int j = 0; j < sizeSquare; j++) {
			cout << origSquare[i][j];
		}
		cout << endl;
	}
	cout << endl;

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