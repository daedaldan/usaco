/*
ID: daniel25
TASK: hamming
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>

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
hamCodes possibleSolutions[1000000];
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
    for (int i = 1; i < c.size; i++) {
//        cout << "distance: " << hammingDistance(c.codes[0].code, c.codes[i].code) << endl;
        if (hammingDistance(c.codes[0].code, c.codes[i].code) < D) {
            return false;
        }
    }

    return true;
}

int binaryToDecimal(code c) {
    int decimal = 0;
    for (int i = 0; i < B; i++) {
        if (c.code[i] == 1)
            decimal += pow(2, i);
    }
    return decimal;
}

bool existing(hamCodes hc, code c) {
    for (int i = 0; i < hc.size; i++) {
        bool same = true;
        for (int j = 0; j < B; j++) {
            if (hc.codes[i].code[j] != c.code[j])
                same = false;
        }
        if (same) return true;
    }

    return false;
}

bool cmpCode(code a, code b) {
    return binaryToDecimal(a) < binaryToDecimal(b);
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
    cout << "here" << endl;

    code emptyC;
    generateCodes(emptyC, 0);
    cout << "here" << endl;
    sort(codes, codes + numCodes, cmpCode);

    hamCodes hc;
    hc.codes[0] = codes[0];
    hc.size++;
    for (int i = 0; i < numCodes; i++) {
        if (hc.size < N) {
            cout << binaryToDecimal(codes[i]) << endl;
            hamCodes hcCopy = hc;
            hcCopy.codes[hcCopy.size] = codes[i];
            hcCopy.size++;
            if (hammingEquality(hcCopy)) {
                cout << "   made it" << endl;
                hc.codes[hc.size] = codes[i];
                hc.size++;
            }
        } else break;
    }

    for (int i = 0; i < hc.size; i++)
        cout << binaryToDecimal(hc.codes[i]) << endl;

    // writing output
    ofstream fout("hamming.out");
    if (fout.is_open()) {
        for (int i = 0; i < hc.size; i++) {
            if ((i+1) % 10 == 0) {
                fout << binaryToDecimal(hc.codes[i]) << "\n";
            } else {
                fout << binaryToDecimal(hc.codes[i]) << " ";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}