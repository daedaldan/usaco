#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct cow {
    int start;
    int end;
    int buckets;
};

int N;
cow cows[100];
int times[1001];
int bucketsNeeded = 0;
int buckets = 0;

int main() {
    // reading input
    ifstream fin("blist.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            cow c = cow();
            fin >> c.start;
            fin >> c.end;
            fin >> c.buckets;
            cows[i] = c;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        times[cows[i].start] = cows[i].buckets;
        times[cows[i].end] = -cows[i].buckets;
    }

    for (int i = 0; i < 1001; i++) {
        if (buckets - times[i] < 0) {
            bucketsNeeded += times[i] - buckets;
            buckets += times[i] - buckets;
        }

        buckets -= times[i];
    }

    // writing output
    ofstream fout("blist.out");
    if (fout.is_open()) {
        fout << bucketsNeeded << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}