#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <set>

using namespace std;

int N;
int degrees[100000];
int grassTypes = 1;

int main() {
    // reading input
    ifstream fin("planting.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N-1; i++) {
            int a, b;
            fin >> a >> b;
            degrees[a-1]++;
            degrees[b-1]++;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        if (degrees[i] > grassTypes)
            grassTypes = degrees[i];
    }

    grassTypes++;

    // writing output
    ofstream fout("planting.out");
    if (fout.is_open()) {
        fout << grassTypes << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}