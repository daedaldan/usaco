#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<int> b1buckets;
vector<int> b2buckets;
set<int> b1sizes;

void solve(int day, int b1, int b2, vector<int> buckets1, vector<int> buckets2) {
    if (day == 5) {
        b1sizes.insert(b1);
        return;
    }

    vector<int> orig1 = buckets1;
    vector<int> orig2 = buckets2;
    int origb1 = b1;
    int origb2 = b2;
    if (day % 2 == 1) {
        for (int i = 0; i < buckets1.size(); i++) {
            b1 -= buckets1[i];
            b2 += buckets1[i];
            buckets2.push_back(buckets1[i]);
            buckets1.erase(buckets1.begin() + i);
            solve(day+1, b1, b2, buckets1, buckets2);
            b1 = origb1;
            b2 = origb2;
            buckets1 = orig1;
            buckets2 = orig2;
        }
    } else {
        for (int i = 0; i < buckets2.size(); i++) {
            b2 -= buckets2[i];
            b1 += buckets2[i];
            buckets1.push_back(buckets2[i]);
            buckets2.erase(buckets2.begin() + i);
            solve(day+1, b1, b2, buckets1, buckets2);
            b1 = origb1;
            b2 = origb2;
            buckets1 = orig1;
            buckets2 = orig2;
        }
    }
}

int main() {
    // reading input
    ifstream fin("backforth.in");
    if (fin.is_open()) {
        for (int i = 0; i < 10; i++) {
            int b;
            fin >> b;
            b1buckets.push_back(b);
        }
        for (int i = 0; i < 10; i++) {
            int b;
            fin >> b;
            b2buckets.push_back(b);
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    solve(1, 1000, 1000, b1buckets, b2buckets);

    // writing output
    ofstream fout("backforth.out");
    if (fout.is_open()) {
        fout << b1sizes.size() << endl;
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}