#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

struct endpoint {
    long t;
    long index;
};

long N;
endpoint endpoints[200000];
set<long> working;
long alone[100000];
long actualTimeCovered = 0;

bool cmp(endpoint a, endpoint b) { return a.t < b.t; }

int main() {
    // reading input
    ifstream fin("lifeguards.in");
    if (fin.is_open()) {
        fin >> N;
        for (long i = 0; i < N; i++) {
            endpoint s;
            endpoint e;
            fin >> s.t;
            fin >> e.t;
            s.index = i;
            e.index = i;
            endpoints[2*i] = s;
            endpoints[2*i+1] = e;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(endpoints, endpoints + 2 * N, cmp);

    long last = 0;
    for (long i = 0; i < 2 * N; i++) {
        if (working.size() == 1) {
            alone[*working.begin()] += endpoints[i].t - last;
        }
        if (!working.empty()) {
            actualTimeCovered += endpoints[i].t - last;
        }
        if (working.find(endpoints[i].index) != working.end()) {
            working.erase(endpoints[i].index);
        } else {
            working.insert(endpoints[i].index);
        }
        last = endpoints[i].t;
    }

    long maxCoveredIfFire = 0;
    for (long i = 0; i < N; i++) {
        if (actualTimeCovered - alone[i] > maxCoveredIfFire)
            maxCoveredIfFire = actualTimeCovered - alone[i];
    }

    // writing output
    ofstream fout("lifeguards.out");
    if (fout.is_open()) {
        fout << maxCoveredIfFire << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}