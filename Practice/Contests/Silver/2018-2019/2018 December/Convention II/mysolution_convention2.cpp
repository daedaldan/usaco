#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct cow {
    long long arrival;
    long long sampling;
    long long seniority;
    bool operator<(const cow & rhs) const {
        return seniority < rhs.seniority;
    }
};

int N;
cow cows[100000];
priority_queue<cow> waiting;
long long maxWaitingTime = -1;
int samplingEnd = -1;

bool arrivalCmp (cow a, cow b) {
    return a.arrival < b.arrival;
}

int main() {
    // reading input
    ifstream fin("convention2.in");
    if (fin.is_open()) {
        fin >> N;
        for (long long i = 0; i < N; i++) {
            cow c;
            fin >> c.arrival;
            fin >> c.sampling;
            c.seniority = N - i;
            cows[i] = c;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(cows, cows+N, arrivalCmp);
    int nextArrival = 1;
    int samplingEnd = cows[0].arrival + cows[0].sampling;
    // while there are still cows that will arrive or are in line
    while (nextArrival < N || waiting.size() > 0) {
        cout << "pew" << endl;
        // cows arriving
        while (nextArrival < N && cows[nextArrival].arrival <= samplingEnd) {
            waiting.push(cows[nextArrival]);
            cout << "ARRIVAL at " << cows[nextArrival].arrival << " of cow who will sample for " << cows[nextArrival].sampling << endl;
            nextArrival++;
        }

        if (waiting.size() == 0 && nextArrival < N) {
            cout << waiting.top().arrival << endl;
            // nobody in line, current grazing cow is done, schedule next cow
            cout << "SAMPLING for cow arrived at " << cows[nextArrival].arrival << " who will sample for " << cows[nextArrival].sampling << endl;
            cout << " waiting time: " << samplingEnd - cows[nextArrival].arrival << endl;
            samplingEnd = cows[nextArrival].arrival + cows[nextArrival].sampling;
            nextArrival++;
        } else if (waiting.size() > 0) {
            cout << waiting.top().arrival << endl;
            // next cow in priority queue scheduled
            long long timeWaited = samplingEnd - waiting.top().arrival;
            if (timeWaited > maxWaitingTime)
                maxWaitingTime = timeWaited;
            samplingEnd += waiting.top().sampling;
            cout << "SAMPLING for cow arrived at " << waiting.top().arrival << " who will sample for " << waiting.top().sampling << endl;
            cout << " waiting time: " << timeWaited << endl;
            waiting.pop();
        }
    }

    // writing output
    ofstream fout("convention2.out");
    if (fout.is_open()) {
        fout << maxWaitingTime << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}