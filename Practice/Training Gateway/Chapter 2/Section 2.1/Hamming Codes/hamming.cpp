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
    code codes[500];
};

int N, B, D;

int hammingDistance(int a[], int b[]) {
    int distance = 0;
    for (int i = 0; i < B; i++)
        if (a[i] != b[i])
            distance += 1;
    return distance;
}

bool hammingEquality(hamCodes c) {
    for (int i = 0; i < c.size; i++) {
        for (int j = 0; j < c.size; j++) {
            if (i != j) {
                if (hammingDistance(c.codes[i].code, c.codes[j].code) < D) {
                    return false;
                }
            }
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

code numToCode(int n) {
    code c = code();
    for (int i = B; i > 0; i--) {
        if (n - pow(2, i-1) >= 0) {
            c.code[i-1] = 1;
            n -= pow(2, i-1);
        } else {
            c.code[i-1] = 0;
        }
    }

    return c;
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

    hamCodes hc;
    hc.codes[0] = numToCode(0);
    hc.size++;
    for (int i = 1; i < pow(2, B); i++) {
        if (hc.size < N) {
            hamCodes hcCopy = hc;
            hcCopy.codes[hcCopy.size] = numToCode(i);
            hcCopy.size++;
            if (hammingEquality(hcCopy)) {
                hc.codes[hc.size] = numToCode(i);
                hc.size++;
            }
        } else break;
    }

    // writing output
    ofstream fout("hamming.out");
    if (fout.is_open()) {
        for (int i = 0; i < hc.size; i++) {
            if ((i+1) % 10 == 0 || i == hc.size-1) {
                fout << binaryToDecimal(hc.codes[i]) << "\n";
            } else {
                fout << binaryToDecimal(hc.codes[i]) << " ";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}