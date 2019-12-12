#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <set>

using namespace std;

struct field {
    int grass = 1;
    bool visited = false;
};

int N;
unordered_set<int> edges[100000];
field fields[100000];
int grassTypes = 1;

void findNeighborGrass(unordered_set<int> & grasses, int field, int level) {
//    cout << "Field " << field << " with grass " << fields[field].grass << ", level: " << level << endl;
    if (level == 0) {
        for (int i = 0; i < N; i++) {
            if (edges[field].find(i) != edges[field].end() && fields[i].visited) {
                findNeighborGrass(grasses, i, level+1);
            }
        }
    } else if (level <= 2) {
        grasses.insert(fields[field].grass);
        for (int i = 0; i < N; i++) {
            if (edges[field].find(i) != edges[field].end() && fields[i].visited) {
                findNeighborGrass(grasses, i, level+1);
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
            edges[a-1].insert(b-1);
            edges[b-1].insert(a-1);
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        if (!fields[i].visited) {
            unordered_set<int> neighborGrasses;
            findNeighborGrass(neighborGrasses, i, 0);
            bool unique = false;
            int fieldGrass = 1;
            while (!unique) {
                // if this grass type is already taken
                if (neighborGrasses.find(fieldGrass) != neighborGrasses.end()) {
                    fieldGrass++;
                } else {
                    unique = true;
                }
//                cout << fieldGrass << endl;
            }
            fields[i].grass = fieldGrass;
            fields[i].visited = true;
            if (fieldGrass > grassTypes)
                grassTypes = fieldGrass;
//            cout << endl;
        }
    }

//    for (int i = 0; i < N; i++)
//        cout << fields[i].grass << endl;


    // writing output
    ofstream fout("planting.out");
    if (fout.is_open()) {
        fout << grassTypes << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}