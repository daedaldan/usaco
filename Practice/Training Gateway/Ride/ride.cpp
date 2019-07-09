/*
ID: daniel25
TASK: ride
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

int main() {
    string comet;
    string group;

    // read input
    ifstream reader("ride.in");
    if (reader.is_open()) {
        getline(reader, comet);
        getline(reader, group);
    } else {
        cout << "ERROR" << endl;
    }
    reader.close();

//    cout << comet << " " << group << endl;

    // initialize map of alphabet letters to numbers
    map<char, int> alpha_num;
    for (int i = 1; i <= 26; i++) {
        alpha_num[(char)(i+64)] = i;
    }

    // calculate number of comet
    int comet_num = 1;
    for (int i = 0; i < comet.length(); i++) {
        comet_num *= alpha_num[comet[i]];
//        cout << comet_num << endl;
    }
    comet_num %= 47;
//    cout << comet_num << endl;

    // calculate number of group
    int group_num = 1;
    for (int i = 0; i < group.length(); i++) {
        group_num *= alpha_num[group[i]];
//        cout << group_num << endl;
    }
    group_num %= 47;
//    cout << group_num << endl;

    // output result
    ofstream writer("ride.out");
    if (comet_num == group_num) {
        writer << "GO\n";
    } else {
        writer << "STAY\n";
    }
    writer.close();

    return 0;
}