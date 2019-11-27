#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int line[100];
int sorted[100];
int numSwaps = 0;

bool equalArrays(int a[], int b[]) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

int main() {
    // reading input
    ifstream fin("outofplace.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            fin >> line[i];
            sorted[i] = line[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(sorted, sorted+N);

    while (!equalArrays(line, sorted)) {
        queue<int> low;
        queue<int> high;
        for (int i = 0; i < N; i++) {
            if (line[i] > sorted[i]) {
                high.push(i);
            } else if (line[i] < sorted[i]){
                low.push(i);
            }
            while (!low.empty() && !high.empty()) {
                int a = low.front();
                int b = high.front();
                int temp = line[b];
                line[b] = line[a];
                line[a] = temp;
                low.pop();
                high.pop();
                numSwaps++;
            }
        }
    }

    // writing output
    ofstream fout("outofplace.out");
    if (fout.is_open()) {
        fout << numSwaps << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}