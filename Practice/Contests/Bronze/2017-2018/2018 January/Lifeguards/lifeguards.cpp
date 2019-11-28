#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct lifeguard {
    int start;
    int end;
};

int N;
lifeguard guards[100];
int shifts[1001];
int startShift = 1009;
int endShift = -1;
int maxTime = -1;

int main() {
    // reading input
    ifstream fin("lifeguards.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            lifeguard g;
            fin >> g.start;
            fin >> g.end;
            if (g.start < startShift)
                startShift = g.start;
            if (g.end > endShift)
                endShift = g.end;
            guards[i] = g;
            for (int j = g.start; j < g.end; j++) {
                shifts[j]++;
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        lifeguard g = guards[i];
        // take off lifeguard's time
        for (int i = g.start; i < g.end; i++) {
            shifts[i]--;
        }
        // check how much time is still covered
        int timeCovered = 0;
        for (int i = startShift; i < endShift; i++) {
            if (shifts[i] > 0)
                timeCovered++;
        }
        // update max time covered if necessary
        if (timeCovered > maxTime)
            maxTime = timeCovered;
        // "reinstall" lifeguard on duty
        for (int i = g.start; i < g.end; i++) {
            shifts[i]++;
        }
    }

    // writing output
    ofstream fout("lifeguards.out");
    if (fout.is_open()) {
        fout << maxTime << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}

