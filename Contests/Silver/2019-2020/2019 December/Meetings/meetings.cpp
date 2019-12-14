#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct cow {
    int weight;
    double location;
    int velocity;
    bool barn = false;
    int numCows = 0;
    bool operator<(cow const & rhs) const {
        return location < rhs.location;
    }
};

int N, L;
cow points[50002];
double barnWeight = 0;
double sumWeight = 0;
int meetings = 0;

int main() {
    // reading input
    ifstream fin("meetings.in");
    if (fin.is_open()) {
        fin >> N >> L;
        cow b1;
        b1.weight = -1;
        b1.location = 0;
        b1.velocity = 0;
        b1.barn = true;
        points[0] = b1;
        cow b2;
        b2.weight = -1;
        b2.location = L;
        b2.velocity = 0;
        b2.barn = true;
        points[1] = b2;
        for (int i = 2; i < N + 2; i++) {
            cow c;
            fin >> c.weight >> c.location >> c.velocity;
            points[i] = c;
            sumWeight += c.weight;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(points, points+N+2);

    while (barnWeight < sumWeight / 2) {
        // find next event
        for (int i = 0; i < N + 2; i++) {
            if (!points[i].barn) {
                if (points[i].velocity == -1) {
                    // this cow and whatever is on the left will meet in
                } else {

                }
            }
        }
    }

    // writing output
    ofstream fout("meetings.out");
    if (fout.is_open()) {
        fout << meetings + N - 1 << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}