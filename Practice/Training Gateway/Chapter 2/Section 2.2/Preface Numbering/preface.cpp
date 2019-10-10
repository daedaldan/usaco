/*
ID: daniel25
TASK: preface
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

int N;
string romanValues[] = {"I", "V", "X", "L", "C", "D", "M"};
int numRomans[] = {0, 0, 0, 0, 0, 0, 0};

int main() {
    // reading input
    ifstream fin("preface.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int a = 1; a <= N; a++) {
        int i = a;
        while (i > 0) {
            if (i >= 1000) {
                i -= 1000;
                numRomans[6] += 1;
            } else if (i >= 900) {
                i -= 900;
                numRomans[4] += 1;
                numRomans[6] += 1;
            } else if (i >= 500) {
                i -= 500;
                numRomans[5] += 1;
            } else if (i >= 400) {
                i -= 400;
                numRomans[4] += 1;
                numRomans[5] += 1;
            } else if (i >= 100) {
                i -= 100;
                numRomans[4] += 1;
            } else if (i >= 90) {
                i -= 90;
                numRomans[2] += 1;
                numRomans[4] += 1;
            } else if (i >= 50) {
                i -= 50;
                numRomans[3] += 1;
            } else if (i >= 40) {
                i -= 40;
                numRomans[2] += 1;
                numRomans[3] += 1;
            } else if (i >= 10) {
                i -= 10;
                numRomans[2] += 1;
            } else if (i >= 9) {
                i -= 9;
                numRomans[0] += 1;
                numRomans[2] += 1;
            } else if (i >= 5) {
                i -= 5;
                numRomans[1] += 1;
            } else if (i >= 4) {
                i -= 4;
                numRomans[0] += 1;
                numRomans[1] += 1;
            } else if (i >= 1) {
                numRomans[0] += i;
                i -= i;
            }
        }
    }

    // writing output
    ofstream fout("preface.out");
    if (fout.is_open()) {
        bool start = false;
        stack<string> toOutput;
        for (int i = 6; i >= 0; i--) {
            if (numRomans[i] > 0)
                start = true;
            if (start) {
                string output = romanValues[i] + " " + to_string(numRomans[i]) + "\n";
                toOutput.push(output);
            }
        }

        while (!toOutput.empty()) {
            fout << toOutput.top();
            toOutput.pop();
        }

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}