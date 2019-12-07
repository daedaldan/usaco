#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct cow {
    int arrival;
    int sampling;
    int seniority;
    bool operator<(const cow & rhs) const {
        return seniority < rhs.seniority;
    }
};

int N;
cow cows[100000];
priority_queue<cow> waiting;
int maxWaitingTime = -1;
bool firstCowArrived = false;
cow samplingCow;
int samplingEnd = -1;

bool arrivalCmp (cow a, cow b) {
    return a.arrival < b.arrival;
}

int main() {
    // reading input
    ifstream fin("convention2.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
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

//    for (int i = 0; i < N; i++) {
//        bool arrived = false;
//        if (!(!waiting.empty() && cows[i].arrival > samplingEnd)) {
//            cout << "ARRIVAL at " << cows[i].arrival << " with seniority " << cows[i].seniority << endl;
//            waiting.push(cows[i]);
//            arrived = true;
//        }
//
//        if (cows[i].arrival >= samplingEnd || cows[i].arrival == samplingCow.arrival) {
//            samplingCow = waiting.top();
//            cout << "SAMPLING for cow that arrived at: " << samplingCow.arrival << " with seniority " << samplingCow.seniority << " who will sample for " << samplingCow.sampling << endl;
//            int waitingTime = samplingEnd - samplingCow.arrival;
//            cout << "    this cow waited for " << waitingTime << endl;
//            if (waitingTime > maxWaitingTime) {
//                maxWaitingTime = waitingTime;
//            }
//            samplingEnd = samplingEnd + samplingCow.sampling;
//            waiting.pop();
//            if (samplingEnd < 0)
//                cout << "    sampling will end at " << 0 << endl;
//            else
//                cout << "    sampling will end at " << samplingEnd << endl;
//        }
//
//        if (!arrived)
//            i--;
//    }

    waiting.push(cows[0]);
    int index = 1;
    while (!waiting.empty()) {
        if (!waiting.empty() && cows[index-1].arrival > samplingEnd) {
            // new cow samples grass
            samplingCow = waiting.top();
            cout << "SAMPLING for cow that arrived at: " << samplingCow.arrival << " with seniority " << samplingCow.seniority << " who will sample for " << samplingCow.sampling << endl;
            int waitingTime = samplingEnd - samplingCow.arrival;
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