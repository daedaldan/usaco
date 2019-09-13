/*
ID: daniel25
TASK: sprime
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
string d1[4] = {"2", "3", "5", "7"};
string d[4] = {"1", "3", "7", "9"};
string possibleSolutions[100000];
int possibleSolutionIndex = 0;
string solutions[50000];
int solutionIndex = 0;

bool is_prime(int a) {
    if (a <= 3)
        return a > 1;
    else if (a % 2 == 0 || a % 3 == 0)
        return false;

    int i = 5;
    while (i*i <= a) {
        if (a % i == 0 || a % (i+2) == 0)
            return false;
        i += 6;
    }

    return true;
}

bool is_superprime(string s) {
    while (s.length() > 0) {
        if (!is_prime(stoi(s)))
            return false;

        s = s.substr(0, s.length()-1);
    }

    return true;
}

void solve(string s) {
    if (s.length() == N) {
        possibleSolutions[possibleSolutionIndex] = s;
        possibleSolutionIndex++;

        return;
    }

    for (int i = 0; i < 4; i++) {
        string sCopy = s + d[i];
        solve(sCopy);
    }
}

int main() {
    // reading input
    ifstream fin("sprime.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < 4; i++)
        solve(d1[i]);

    for (int i = 0; i < possibleSolutionIndex; i++)
        if (is_superprime(possibleSolutions[i])) {
            solutions[solutionIndex] = possibleSolutions[i];
            solutionIndex++;
        }

    // writing output
    ofstream fout("sprime.out");
    if (fout.is_open()) {
        for (int i = 0; i < solutionIndex; i++)
            fout << solutions[i] << endl;
    } else cout << "error opening output file" << endl;
    fout.close();
}