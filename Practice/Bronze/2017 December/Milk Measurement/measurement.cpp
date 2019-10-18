#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct cow {
    int milk = 7;
};

struct maxMilk {
    int milk = 7;
    vector<string> names = {"Bessie", "Elsie", "Mildred"};
};

struct change {
    int day = -1;
    string name = "no name";
    int milk = -1;
};

int N;
cow bessie;
cow elsie;
cow mildred;
change changes[100];
maxMilk m;
int updates = 0;

int cmp(change a, change b) {return a.day < b.day;}

bool newMax(cow & a, cow & b, cow & c) {
    // initialize new max
    maxMilk newM;
    vector<string> emptyVector;
    newM.names = emptyVector;
    newM.milk = -1;

    //  updating new max
    if (bessie.milk == newM.milk) {
        newM.milk = bessie.milk;
        newM.names.push_back("Bessie");
    } else if (bessie.milk > newM.milk) {
        newM.milk = bessie.milk;
        newM.names = emptyVector;
        newM.names.push_back("Bessie");
    }

    if (elsie.milk == newM.milk) {
        newM.milk = elsie.milk;
        newM.names.push_back("Elsie");
    } else if (elsie.milk > newM.milk) {
        newM.milk = elsie.milk;
        newM.names = emptyVector;
        newM.names.push_back("Elsie");
    }

    if (mildred.milk == newM.milk) {
        newM.milk = mildred.milk;
        newM.names.push_back("Mildred");
    } else if (mildred.milk > newM.milk) {
        newM.milk = mildred.milk;
        newM.names = emptyVector;
        newM.names.push_back("Mildred");
    }

    // checking for changes in max cows
    if (newM.names.size() != m.names.size()) {
        m = newM;
        return true;
    }
    sort(newM.names.begin(), newM.names.end());
    sort(m.names.begin(), m.names.end());
    for (int i = 0; i < newM.names.size(); i++) {
        if (m.names[i] != newM.names[i]) {
            m = newM;
            return true;
        }
    }

    // no changes
    return false;
}

int main() {
    // reading input
    ifstream fin("measurement.in");
    if (fin.is_open()) {
        string line;
        getline(fin, line);
        N = stoi(line);
        for (int i = 0; i < N; i++) {
            change c;
            getline(fin, line);
            c.day = stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1, line.length());
            c.name = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ")+1, line.length());
            c.milk = stoi(line.substr(0));
            changes[i] = c;
        }
        sort(changes, changes+N, cmp);
    } else cout << "error opening input file" << endl;
    fin.close();

    // making changes
    for (int i = 0; i < N; i++) {
        if (changes[i].name == "Bessie") {
            bessie.milk += changes[i].milk;
        } else if (changes[i].name == "Elsie") {
            elsie.milk += changes[i].milk;
        } else if (changes[i].name == "Mildred") {
            mildred.milk += changes[i].milk;
        }

        if (newMax(bessie, elsie, mildred)) updates++;
    }

    // writing output
    ofstream fout("measurement.out");
    if (fout.is_open()) {
        fout << updates;
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}