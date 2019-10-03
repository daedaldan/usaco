/*
ID: daniel25
TASK: hamming
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct code {
    int code[8];
};

struct hamCodes {
    int size = 0;
    code codes[16];
};

int N, B, D;
code codes[256];
hamCodes possibleSolutions[1000];
int numCodes = 0;
int numPossibleSolutions = 0;
int minValue = 99999999;
hamCodes solution;

void generateCodes(code c, int len) {
    if (len == B) {
        codes[numCodes] = c;
        numCodes++;
    } else {
        code c1 = c;
        c1.code[len] = 0;
        generateCodes(c1, len+1);
        code c2 = c;
        c2.code[len] = 1;
        generateCodes(c2, len+1);
    }
}

int hammingDistance(int a[], int b[]) {
    int distance = 0;
    for (int i = 0; i < B; i++)
        if (a[i] != b[i])
            distance += 1;
    return distance;
}

bool hammingEquality(hamCodes c) {
    for (int i = 1; i < c.size; i++)
        if (hammingDistance(c.codes[0].code, c.codes[i].code) != D)
            return false;
    return true;
}

bool existing(hamCodes hc, code c) {
    for (int i = 0; i < hc.size; i++) {
        for (int j = 0; j < B; j++) {
            if (hc.codes[i].code[j] == c.code[j])
                return true;
        }
    }
    return false;
}

int binaryToDecimal(code c) {
    int decimal = 0;
    for (int i = 0; i < B; i++) {
        if (c.code[i] == 1)
            decimal += pow(2, i);
    }
    return decimal;
}

void generatePossibleSolutions(hamCodes c) {
//    if (binaryToDecimal(c.codes[1]) == 7) cout << "here" << endl;
    if (c.size == N) {
        for (int i = 0; i < c.size; i++) {
            cout << binaryToDecimal(c.codes[i]) << " ";
        }
        cout << endl;
        possibleSolutions[numPossibleSolutions] = c;
        numPossibleSolutions++;
    } else {
        for (int i = 0; i < numCodes; i++) {
//            if (binaryToDecimal(codes[i]) == 25) cout << "here" << " " << c.size << endl;
            if (!existing(c, codes[i])) {
                hamCodes cCopy = c;
                cCopy.codes[cCopy.size] = codes[i];
                if (hammingEquality(cCopy)) {
                    cCopy.size++;
                    generatePossibleSolutions(cCopy);
                }
            }
        }
    }
}

void findOptimalSolution() {
    for (int i = 0; i < numPossibleSolutions; i++) {
        int sum = 0;
        for (int j = 0; j < possibleSolutions[i].size; j++) {
            sum += binaryToDecimal(possibleSolutions[i].codes[j]);
        }
        if (sum < minValue) {
            minValue = sum;
            solution = possibleSolutions[i];
        }
    }
}

int main() {
    // reading input
    ifstream fin("hamming.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> B;
        fin >> D;
    } else cout << "error opening input file" << endl;
    fin.close();

    code emptyC;
    generateCodes(emptyC, 0);
//    for (int i = 0; i < numCodes; i++) {
//        for (int j = 0; j < B; j++) {
//            cout << codes[i].code[j];
//        }
//        cout << endl;
//    }
    hamCodes emptyHC;
    generatePossibleSolutions(emptyHC);
    cout << "# of possible solutions: " << numPossibleSolutions << endl;
    findOptimalSolution();

    int a[8];
    a[0] = 1;
    a[1] = 1;
    a[2] = 1;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    int b[8];
    b[0] = 1;
    b[1] = 1;
    b[2] = 0;
    b[3] = 0;
    b[4] = 1;
    b[5] = 0;
    b[6] = 0;
    b[7] = 0;
    cout << hammingDistance(a, b) << endl;

    // writing output
    ofstream fout("hamming.out");
    if (fout.is_open()) {
        for (int i = 0; i < solution.size; i++) {
            if ((i+1) % 10 == 0) {
                fout << binaryToDecimal(solution.codes[i]) << "\n";
            } else {
                fout << binaryToDecimal(solution.codes[i]) << " ";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}