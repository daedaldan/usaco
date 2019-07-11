/*
ID: daniel25
TASK: gift1
LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    // reading input
    ifstream reader("gift1.in");
//    ifstream reader("input.txt");
    string inputLine;
    vector<string> input;
    if (reader.is_open()) {
        while (getline(reader, inputLine)) {
            input.push_back(inputLine);
        }
    } else {
        cout << "error opening input file" << endl;
    }
    reader.close();

    // making map of the friends and their cash, initialized to 0
    map<string, int> peopleCash;

    for (int i = 1; i <= stoi(input[0]); i++) {
        peopleCash[input[i]] = 0;
    }

    int step = stoi(input[0]) + 1;

    // distributing cash
    while (step < input.size()) {
        string currentGiver = input[step];
        int givenCash = stoi(input[step+1].substr(0, input[step+1].find(" ")));
        int friendsGivenTo = stoi(input[step + 1].substr(input[step+1].find(" ") + 1, input[step+1].length()));
        int cashToEachFriend = 0;
        if (friendsGivenTo != 0) {
            cashToEachFriend = (givenCash - (givenCash % friendsGivenTo)) / friendsGivenTo;
            peopleCash[currentGiver] -= givenCash - (givenCash % friendsGivenTo);
        }
        for (int i = step + 2; i < step + 2 + friendsGivenTo; i++) {
            peopleCash[input[i]] += cashToEachFriend;
        }
        step += 2 + friendsGivenTo;
    }

    ofstream writer("gift1.out");
//    ofstream writer("output.txt");
    if (writer.is_open()) {
        for (int i = 1; i <= stoi(input[0]); i++) {
            writer << input[i] << " " << peopleCash[input[i]] << "\n";
        }
    } else {
        cout << "error opening writer file" << endl;
    }
    writer.close();

    return 0;
}