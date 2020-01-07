#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct cow {
    int w;
    int x;
    int d;
    bool operator<(const cow & rhs) const {
        return x < rhs.x;
    }
};

int N, L;
long T;
double weightT = 0;
cow cows[50000];
pair<int, int> finishing[50000];
int meetings = 0;

int main() {
    // reading input
    ifstream fin("meetings.in");
    if (fin.is_open()) {
        fin >> N >> L;
        for (int i = 0; i < N; i++) {
            cow c;
            fin >> c.w >> c.x >> c.d;
            cows[i] = c;
            weightT += c.w;
        }
        weightT /= 2.0;
    } else cout << "error opening input file" << endl;
    fin.close();

    int left[50000];
    int numLeft = 0;
    int right[50000];
    int numRight = 0;

    sort(cows, cows+N);
    // finding finishing times of cows and their respective weights
    for (int i = 0; i < N; i++) {
        if (cows[i].d == 1) {
            right[numRight] = cows[i].x;
            numRight++;
        } else if (cows[i].d == -1) {
            left[numLeft] = cows[i].x;
            numLeft++;
        }
    }

    // left cows
    for (int i = 0; i < numLeft; i++) {
        finishing[i].first = left[i];
        finishing[i].second = cows[i].w;
    }

    // right cows
    for (int i = 0; i < numRight; i++) {
        finishing[numLeft+i].first = L-right[i];
        finishing[numLeft+i].second = cows[numLeft+i].w;
    }
    sort (finishing, finishing+N);

    // finding T
    int total = 0;
    for (int i = 0; i < N; i++) total += finishing[i].second;
    int i = 0;
    while (total > 0) {
        total -= 2*finishing[i].second;
        i++;
    }
    T = finishing[i-1].first;

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (cows[i].d == -1) {
            while (q.size() > 0 && q.front() + 2*T < cows[i].x) q.pop();
            meetings += q.size();
        } else {
            q.push(cows[i].x);
        }
    }

    // writing output
    ofstream fout("meetings.out");
    if (fout.is_open()) {
        fout << meetings << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}