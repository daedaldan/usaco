#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct cow {
    long long arrival;
    long long sampling;
    long long seniority;
    bool operator<(const cow & rhs) const {
        return seniority < rhs.seniority;
    }
};

long long N;
cow cows[100000];
priority_queue<cow> waiting;
long long maxWaitingTime = -1;
bool firstCowArrived = false;
cow samplingCow;
long long samplingEnd = -1;

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
    samplingEnd = cows[0].arrival;

    waiting.push(cows[0]);
    int index = 1;
    while (!waiting.empty()) {
        cout << waiting.size() << endl;
        if (!waiting.empty() && (cows[index].arrival > samplingEnd || index == N)) {
            // new cow samples grass
            samplingCow = waiting.top();
            cout << "SAMPLING for cow that arrived at: " << samplingCow.arrival << " with seniority " << samplingCow.seniority << " who will sample for " << samplingCow.sampling << endl;
            long long waitingTime = samplingEnd - samplingCow.arrival;
            cout << "    this cow waited for " << waitingTime << endl;
            if (waitingTime > maxWaitingTime) {
                maxWaitingTime = waitingTime;
            }
            samplingEnd = samplingEnd + samplingCow.sampling;
            waiting.pop();
            if (samplingEnd < 0)
                cout << "    sampling will end at " << 0 << endl;
            else
                cout << "    sampling will end at " << samplingEnd << endl;
        }

        // another cow arrives
        if ((waiting.empty() || cows[index].arrival <= samplingEnd) && index < N) {
            cout << "ARRIVAL at " << cows[index].arrival << " with seniority " << cows[index].seniority << endl;
            waiting.push(cows[index]);
            index++;
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