/*
ID: daniel25
TASK: concom
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct company {
    int ownings = 0;
    bool visited = false;
    int ownedCompanies[101];
    int shares[101];
};

struct owning {
    int owner = -1;
    int owned = -1;
};

int N;
owning solutions[10000];
int numSolutions = 0;
company companies[101];
int numCompanies = 0;

bool cmp(owning a, owning b) {
    if (a.owner != b.owner) {
        return a.owner < b.owner;
    } else {
        return a.owned < b.owned;
    }
}

void initializeArrays() {
    // setting all shares to 0
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            companies[i].shares[j] = 0;
        }
    }

    // setting each company to own itself
    for (int i = 1; i <= 100; i++) {
        companies[i].shares[i] = 999;
    }
}

void evaluate (int compNum) {
    if (!companies[compNum].visited) {
        companies[compNum].visited = true;
        for (int i = 0; i < companies[compNum].ownings; i++) {
                evaluate(companies[compNum].ownedCompanies[i]);
        }

        for (int i = 0; i < companies[compNum].ownings; i++) {
            if (companies[compNum].shares[companies[compNum].ownedCompanies[i]] >= 50) {
                company ownedComp = companies[companies[compNum].ownedCompanies[i]];
                for (int j = 0; j < ownedComp.ownings; j++) {
                    companies[compNum].shares[ownedComp.ownedCompanies[j]] += ownedComp.shares[ownedComp.ownedCompanies[j]];
                    bool found = false;
                    for (int k = 0; k < companies[compNum].ownings; k++) {
                        if (companies[compNum].ownedCompanies[k] == ownedComp.ownedCompanies[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        companies[compNum].ownedCompanies[companies[compNum].ownings] = ownedComp.ownedCompanies[j];
                        companies[compNum].ownings++;
                    }

                }
            }
        }
    }
}

void evaluateAll() {
    for (int i = 1; i <= numCompanies; i++) {
        if (!companies[i].visited) {
            evaluate(i);
        }
    }
}

int main() {
    // setting all shares to 0 and each company to own itself
    initializeArrays();

    // reading input
    ifstream fin("concom.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            int owner;
            int owning;
            int share;
            fin >> owner;
            fin >> owning;
            fin >> share;
            companies[owner].shares[owning] += share;
            companies[owner].ownedCompanies[companies[owner].ownings] = owning;
            companies[owner].ownings++;
            if (max(owning, owner) > numCompanies) {
                numCompanies = max(owning, owner);
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    company companiesCopy[101];
    for (int i = 0; i < 101; i++) {
        companiesCopy[i] = companies[i];
    }
    // adding subsidiaries' shares to companies
    evaluateAll();

    // finding companies that own one another
    for (int i = 1; i <= numCompanies; i++) {
        cout << i << " owns:" << endl;
        for (int j = 0; j < companies[i].ownings; j++) {
            cout << "   " << companies[i].shares[companies[i].ownedCompanies[j]] << " of " << companies[i].ownedCompanies[j] << endl;
            if (companies[i].shares[companies[i].ownedCompanies[j]] >= 50 && i != companies[i].ownedCompanies[j]) {
                solutions[numSolutions].owner = i;
                solutions[numSolutions].owned = companies[i].ownedCompanies[j];
                numSolutions++;
            }
        }
    }

    sort(solutions, solutions + numSolutions, cmp);

    // writing output
    ofstream fout("concom.out");
    if (fout.is_open()) {
        for (int i = 0; i < numSolutions; i++) {
            fout << solutions[i].owner << " " << solutions[i].owned << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}