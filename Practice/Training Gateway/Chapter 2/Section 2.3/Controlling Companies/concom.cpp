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

        // adding companies' subsidiaries' shares to its own
        for (int i = 0; i < companies[compNum].ownings; i++) {
            // if the company owns the company it has shares in
            if (companies[compNum].shares[companies[compNum].ownedCompanies[i]] >= 50 && companies[compNum].ownedCompanies[i] != compNum) {
                company ownedComp = companies[companies[compNum].ownedCompanies[i]];
                for (int j = 0; j < ownedComp.ownings; j++) {
                    companies[compNum].shares[ownedComp.ownedCompanies[j]] += ownedComp.shares[ownedComp.ownedCompanies[j]];

                    // checking if subsidiary's subsidiary is in original company's ownings
                    bool found = false;
                    for (int k = 0; k < companies[compNum].ownings; k++) {
                        if (companies[compNum].ownedCompanies[k] == ownedComp.ownedCompanies[j]) {
                            found = true;
                            break;
                        }
                    }

                    // if subsidiary's subsidiary is not in original company's ownings,
                    // then add to original company's ownings
                    if (!found && companies[compNum].shares[ownedComp.ownedCompanies[j]] >= 50) {
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

    // adding subsidiaries' shares to companies
    evaluateAll();

    // finding companies that own one another
    for (int i = 1; i <= numCompanies; i++) {
        for (int j = 0; j < companies[i].ownings; j++) {
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