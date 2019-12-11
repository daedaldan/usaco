#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

struct field {
    int grass = 1;
    bool visited = false;
};

int N;
bool edges[100000][100000];
field fields[100000];
int grassTypes = 1;

void findNeighborGrass(int & lowestGrass, int field, int level) {
    cout << field << " " << fields[field].grass << " " << lowestGrass << " " << level << endl;
    if (level == 0) {
        for (int i = 0; i < N; i++) {
            if (edges[field][i] && fields[i].visited) {
                findNeighborGrass(lowestGrass, i, level+1);
            }
        }
    } else if (level <= 2) {
        if (fields[field].grass == lowestGrass) {
            lowestGrass++;
        }
        cout << "here" << " " << lowestGrass << endl;
        for (int i = 0; i < N; i++) {
            if (edges[field][i] && fields[i].visited) {
                findNeighborGrass(lowestGrass, i, level+1);
            }
        }
    }
}

int main() {
    // reading input
    ifstream fin("planting.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N-1; i++) {
            int a, b;
            fin >> a >> b;
            edges[a-1][b-1] = true;
            edges[b-1][a-1] = true;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        if (!fields[i].visited) {
            int fieldGrass = 1;
            findNeighborGrass(fieldGrass, i, 0);
            fields[i].grass = fieldGrass;
            fields[i].visited = true;
            if (fieldGrass > grassTypes)
                grassTypes = fieldGrass;
            cout << endl;
        }
    }

    for (int i = 0; i < N; i++)
        cout << fields[i].grass << endl;


    // writing output
    ofstream fout("planting.out");
    if (fout.is_open()) {
        fout << grassTypes << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}