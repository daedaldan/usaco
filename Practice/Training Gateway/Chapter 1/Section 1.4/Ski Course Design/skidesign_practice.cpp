/*
ID: daniel25
TASK: skidesign
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

int N, heights[1000];
int minCost = 1000000000;
int cap = 17;

int find_min(int a[]) {
    int min = 101;
    int minI;
    for (int i = 0; i < N; i++) {
        if (a[i] < min) {
            min = a[i];
            minI = i;
        }
    }

    return minI;
}

int find_max(int a[]) {
    int max = -1;
    int maxI;
    for (int i = 0; i < N; i++) {
        if (a[i] > max) {
            max = a[i];
            maxI = i;
        }
    }

    return maxI;
}

void print_heights() {
    for (int i = 0; i < N; i++)
        cout << heights[i] << " ";
    cout << endl;
}

int main() {
    // reading input
    ifstream fin("skidesign.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++)
            fin >> heights[i];
    } else cout << "error opening input file" << endl;
    fin.close();

    print_heights();

    while (cap <= heights[find_max(heights)]) {
        int cost = 0;
        for (int i = 0; i < N; i++) {
            int difference = 0;
            if (heights[i] < cap - 17) {
                difference = cap - 17 - heights[i];
            } else if (heights[i] > cap) {
                difference = heights[i] - cap;
            }

            cost += pow(difference, 2);
        }

        if (cost < minCost)
            minCost = cost;

        cap += 1;
    }

    // writing output
    ofstream fout("skidesign.out");
    if (fout.is_open()) {
        fout << minCost << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}