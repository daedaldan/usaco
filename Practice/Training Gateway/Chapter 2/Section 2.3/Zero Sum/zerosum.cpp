/*
ID: daniel25
TASK: zerosum
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct state {
    int i = 0;
    string expression[18] = {"+", "1", " ", "2", " ", "3", " ", "4", " ", "5", " ", "6", " ", "7", " ", "8", " ", "9"};
};

int N;
state solutions[6561];
int numSolutions = 0;

bool cmp(state a, state b) {
    int i = 0;
    while (a.expression[i] != b.expression[i])
        i++;
    return a.expression[i] < b.expression[i];
}

void printState(state & s) {
    for (int i = 0; i < s.i; i++)
        cout << s.expression[i];
    cout << endl;
}

bool isOp(string s) {
    if (s == "+" || s == "-")
        return true;
    else
        return false;
}

bool evaluateState(state s) {
    string currentNum;
    int sum = 0;
    for (int i = 0; i < s.i; i++) {
        if(isOp(s.expression[i])) {
            currentNum += s.expression[i];
            i++;
            while(!isOp(s.expression[i]) && i < s.i) {
                if (s.expression[i] != " ")
                    currentNum += s.expression[i];
                i++;
            }
            cout << stoi(currentNum) << endl;
            sum += stoi(currentNum);
            currentNum = "";
            i--;
        }
    }

    if (sum == 0)
        return true;
    else
        return false;
}

void findSolutions(state & s) {
    s.i += 2;
    if (s.i == N * 2) {
        if (evaluateState(s)) {
//            printState(s);
            solutions[numSolutions] = s;
            numSolutions++;
        }
    } else {
        state original = s;
        s.expression[s.i] = " ";
        findSolutions(s);
        s = original;
        s.expression[s.i] = "+";
        findSolutions(s);
        s = original;
        s.expression[s.i] = "-";
        findSolutions(s);
        s = original;
    }
}

int main() {
    // reading input
    ifstream fin("zerosum.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    state a;
    findSolutions(a);
    cout << numSolutions << endl;

    sort(solutions, solutions + numSolutions, cmp);

    // writing output
    ofstream fout("zerosum.out");
    if (fout.is_open()) {
        for (int i = 0; i < numSolutions; i++) {
            for (int j = 1; j < solutions[i].i; j++)
                fout << solutions[i].expression[j];
            fout << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}