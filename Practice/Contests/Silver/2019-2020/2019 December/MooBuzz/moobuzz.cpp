#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int firstEight[8];
long solution;

void findFirstEight() {
    int numFound = 0;
    int i = 1;
    while (numFound < 8) {
        if (i % 3 != 0 && i % 5 != 0) {
            firstEight[numFound] = i;
            numFound++;
        }
        i++;
    }
}

int main() {
    // reading input
    ifstream fin("moobuzz.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    findFirstEight();

    if (N <= 8) {
        solution = firstEight[N-1];
    } else {
        int num = (N - 1) / 8;
        solution = firstEight[N - 8 * num - 1] + num * 15;
    }

    // writing output
    ofstream fout("moobuzz.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}

