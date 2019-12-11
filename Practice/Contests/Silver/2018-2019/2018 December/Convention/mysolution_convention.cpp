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

int numCows, numBuses, cowsPerBus;
cow cows[100000];
int maxWait = 0;

bool possible(int maxWaiting) {
    int buses = 1;
    for (int i = 0; i < numCows; i++) {
        int cowsInBus = 0;
        int firstArrival = cows[i].arrival;
        while (cows[i].arrival - firstArrival <= maxWaiting && cowsInBus < cowsPerBus) {
//            cout << i << endl;
            cowsInBus++;
//            cout << "cow arrives at " << cows[i].arrival << " in bus " << buses << " and waiting is " <<  cows[i].arrival - firstArrival << endl;
            i++;
        }
        i--;
        buses++;
    }
    buses--;

    if (buses <= numBuses)
        return true;
    else
        return false;
}

int binarySearch(long low, long high) {
    long mid = (low + high) / 2;
    if (low == high) {
        return mid;
    } else if (low+1 == high) {
        if (possible(low)) {
            return low;
        } else {
            return high;
        }
    } else if (possible(mid))
        binarySearch(low, mid);
    else
        binarySearch(mid, high);
}

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

    sort(cows, cows+numCows);

    // writing output
    ofstream fout("convention.out");
    if (fout.is_open()) {
        fout << binarySearch(0, 1000000000) << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}