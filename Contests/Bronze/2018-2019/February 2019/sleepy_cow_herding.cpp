//
//  sleepy_cow_herding.cpp
//  usaco
//
//  Created by Daniel Wang on 2/24/19.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

string readInput(string filename) {
    ifstream inputStream(filename.c_str());
    string input;
    getline(inputStream, input);
    inputStream.close();
    return input;
}

void writeOutput(string filename, string output) {
    ofstream outputStream(filename.c_str(), fstream::app);
    outputStream << output << endl;
    outputStream.close();
}

//int main() {
//    // reading input data
//    string inputData = readInput("input1.txt");
//    int cow1 = (int)inputData[0] - 48;
//    int cow2 = (int)inputData[2] - 48;
//    int cow3 = (int)inputData[4] - 48;
//
//    // find min number of moves
//    if (abs(cow1 - cow2) == 1 && abs(cow2 - cow3) == 1) writeOutput("output1.txt", "0");
//    else if (abs(cow1 - cow2) == 2 || abs(cow2 - cow3) == 2) writeOutput("output1.txt", "1");
//    else writeOutput("output1.txt", "2");
//
//    // find max number of moves
//    int maxMoves = max(abs(cow1 - cow2), abs(cow2 - cow3)) - 2;
//    cout << maxMoves << endl;
//    writeOutput("output1.txt", to_string(maxMoves));
//
//    return 0;
//}

int main() {
    // reading input data
    string inputData = readInput("herding.in");
    int cow1 = (int)inputData[0] - 48;
    int cow2 = (int)inputData[2] - 48;
    int cow3 = (int)inputData[4] - 48;

    // find min number of moves
    if (abs(cow1 - cow2) == 1 && abs(cow2 - cow3) == 1) writeOutput("herding.out", "0");
    else if (abs(cow1 - cow2) == 2 || abs(cow2 - cow3) == 2) writeOutput("herding.out", "1");
    else writeOutput("herding.out", "2");

    // find max number of moves
    int maxMoves = max(abs(cow1 - cow2), abs(cow2 - cow3)) - 2;
    writeOutput("herding.out", to_string(maxMoves));

    return 0;
}

