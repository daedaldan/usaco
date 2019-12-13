#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct ordering {
    vector<string> cows;
};


int N;
string constraints[7][2];
ordering solutions[45000];
int numSolutions = 0;
ordering permutations[45000];
int numPerms = 0;

bool orderingCmp(ordering a, ordering b) {
    int i = 0;
    while (a.cows[i] == b.cows[i]) {
        i++;
    }
    return a.cows[i] < b.cows[i];
}

void createPermutations (ordering soFar, ordering cowsLeft) {
    if (soFar.cows.size() < 8) {
        ordering originalSoFar = soFar;
        ordering originalCowsLeft = cowsLeft;
        for (int i = 0; i < cowsLeft.cows.size(); i++) {
            soFar.cows.push_back(cowsLeft.cows[i]);
            cowsLeft.cows.erase(cowsLeft.cows.begin() + i);
            createPermutations(soFar, cowsLeft);
            soFar = originalSoFar;
            cowsLeft = originalCowsLeft;
        }
    } else {
        permutations[numPerms] = soFar;
        numPerms++;
    }
}

bool satisfiesConstraint(ordering cows, string a, string b) {
    int i = 0;
    while (cows.cows[i] != a && cows.cows[i] != b) {
        i++;
    }
    if (cows.cows[i] == a) {
        if (i == 7) {
            if (cows.cows[i-1] == b)
                return true;
            else
                return false;
        } else if (i == 0) {
            if (cows.cows[i+1] == b)
                return true;
            else
                return false;
        } else {
            if (cows.cows[i-1] == b)
                return true;
            if (cows.cows[i+1] == b)
                return true;
            return false;
        }
    } else {
        if (i == 7) {
            if (cows.cows[i-1] == a)
                return true;
            else
                return false;
        } else if (i == 0) {
            if (cows.cows[i+1] == a)
                return true;
            else
                return false;
        } else {
            if (cows.cows[i-1] == a)
                return true;
            if (cows.cows[i+1] == a)
                return true;
            return false;
        }
    }
}

int main() {
    // reading input
    ifstream fin("lineup.in");
    if (fin.is_open()) {
        fin >> N;
        string a;
        string b;
        for (int i = 0; i < N; i++) {
            fin >> a;
            fin >> b;
            fin >> b;
            fin >> b;
            fin >> b;
            fin >> b;
            constraints[i][0] = a;
            constraints[i][1] = b;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    ordering soFar;
    ordering cowsLeft;
    cowsLeft.cows.push_back("Bessie");
    cowsLeft.cows.push_back("Buttercup");
    cowsLeft.cows.push_back("Beatrice");
    cowsLeft.cows.push_back("Belinda");
    cowsLeft.cows.push_back("Bella");
    cowsLeft.cows.push_back("Blue");
    cowsLeft.cows.push_back("Betsy");
    cowsLeft.cows.push_back("Sue");
    createPermutations(soFar, cowsLeft);

    for (int i = 0; i < numPerms; i++) {
        bool satisfies = true;
        for (int j = 0; j < N; j++) {
            if (satisfiesConstraint(permutations[i], constraints[j][0], constraints[j][1])) {
                continue;
            } else {
                satisfies = false;
                break;
            }
        }
        if (satisfies) {
            solutions[numSolutions] = permutations[i];
            numSolutions++;
        }
    }

    sort(solutions, solutions + numSolutions, orderingCmp);

    cout << numSolutions << endl;

    // writing output
    ofstream fout("lineup.out");
    if (fout.is_open()) {
        for (int i = 0; i < 8; i++) {
            fout << solutions[0].cows[i] << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}