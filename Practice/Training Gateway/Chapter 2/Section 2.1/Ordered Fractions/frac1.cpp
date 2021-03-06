/*
ID: daniel25
TASK: frac1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int N;
string fracs[12880];
int numFracs;

double fracStrToDouble(string a) {
    return stod(a.substr(0, a.find("/"))) / stod(a.substr(a.find("/")+1));
}

bool fracComp(string a, string b) {
    if (fracStrToDouble(a) >= fracStrToDouble(b)) {
        return false;
    } else if (fracStrToDouble(b) > fracStrToDouble(a)) {
        return true;
    }
}

int gcd(int a, int b) {
    int gcd = -1;
    for (int i = 1; i <= max(a, b); i++) {
        if ((a % i == 0) && (b % i == 0) && (i > gcd))
            gcd = i;
    }

    return gcd;
}

int main() {
    // reading input
    ifstream fin("frac1.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    fracs[0] = "0/1";
    fracs[1] = "1/1";
    numFracs = 2;
    for (int d = 2; d <= N; d++) {
        for (int n = 1; n < d; n++) {
            if (gcd(n, d) == 1) {
                fracs[numFracs] = to_string(n) + "/" + to_string(d);
                numFracs++;
            }
        }
    }

    sort(fracs, fracs+numFracs, fracComp);

    // writing output
    ofstream fout("frac1.out");
    if (fout.is_open()) {
        for (int i = 0; i < numFracs; i++) {
                fout << fracs[i] << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}