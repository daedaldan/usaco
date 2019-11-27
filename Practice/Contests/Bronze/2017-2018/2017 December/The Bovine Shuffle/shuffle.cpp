#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int theShuffle[100];
int endOrder[100];
int originalOrder[100];

int main() {
    // reading input
    ifstream fin("shuffle.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            fin >> theShuffle[i];
        }
        for (int i = 0; i < N; i++) {
            fin >> endOrder[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            originalOrder[j] = endOrder[theShuffle[j]-1];
        }
        for (int a = 0; a < N; a++)
            endOrder[a] = originalOrder[a];
    }

    // writing output
    ofstream fout("shuffle.out");
    if (fout.is_open()) {
        for (int i = 0; i < N; i++)
            fout << originalOrder[i] << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}