#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct cow {
    int arrival;
    bool operator<(const cow & c) const {
        return arrival < c.arrival;
    }
};

struct bus {
    int cows = 0;
    int leave;
};

int numCows, numBuses, cowsPerBus;
cow cows[100000];
int maxWait = 0;

int main() {
    // reading input
    ifstream fin("convention.in");
    if (fin.is_open()) {
        fin >> numCows >> numBuses >> cowsPerBus;
        for (int i = 0; i < numCows; i++) {
            cow c;
            fin >> c.arrival;
            cows[i] = c;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(cows, cows + numCows);

    int cowIndex = 0;
    for (int i = 0; i < numBuses; i++) {
        bus b;
        int minArrival = cows[cowIndex].arrival;
        while (b.cows < cowsPerBus && cowIndex < numCows) {
            b.cows++;
            cowIndex++;
        }
        b.leave = cows[cowIndex-1].arrival;
//        cout << b.leave - minArrival << endl;
        if (b.leave - minArrival > maxWait)
            maxWait = b.leave - minArrival;
    }

    // writing output
    ofstream fout("convention.out");
    if (fout.is_open()) {
        fout << maxWait << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}