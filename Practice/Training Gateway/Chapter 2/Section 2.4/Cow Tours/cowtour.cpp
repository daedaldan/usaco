/*
ID: daniel25
TASK: cowtour
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

struct pasture {
    int x;
    int y;
    int componentNum = -1;
    bool visited = false;
};

struct field {
    int numPastures = 0;
    pasture pastures[150];
};

int N;
pasture pastures[150];
int edges[150][150];
field fields[150];
int numFields = 0;
pasture minPastureA;
pasture minPastureB;
double minDiameter = 999999999.0;

void printEdges() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double distance(pasture a, pasture b) {
    return 1.0;
}

void floodFillDFS(int pastureI) {
    if (!pastures[pastureI].visited) {
        pastures[pastureI].visited = true;
        fields[numFields].pastures[fields[numFields].numPastures] = pastures[pastureI];
        fields[numFields].numPastures++;
        for (int i = 0; i < N; i++) {
            if (edges[pastureI][i] == 1) {
                floodFillDFS(i);
            }
        }
    }
}

void floodFill() {
    for (int i = 0; i < N; i++) {
        if (!pastures[i].visited) {
            floodFillDFS(i);
            numFields++;
        }
    }
}

double findDiameter(field f) {

}

int main() {
    // reading input
    ifstream fin("cowtour.in");
    if (fin.is_open()) {
        fin >> N;
        // reading in pasture locations
        for (int i = 0; i < N; i++) {
            pasture p;
            fin >> p.x >> p.y;
            pastures[i] = p;
        }

        // reading in adjacency matrix
        int i, j = 0;
        for (int i = 0; i < N; i++) {
            string row;
            fin >> row;
            for (int j = 0; j < N; j++) {
                edges[i][j] = row[j] - 48;
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // flood fill to find all fields
    floodFill();

    // pairing two different fields
    for (int i = 0; i < numFields; i++) {
        for (int j = i+1 ; j < numFields; j++) {
            // pairing two pastures in each of the fields
            for (int p1 = 0; p1 < fields[i].numPastures; p1++) {
                for (int p2 = 0; p2 < fields[j].numPastures; p2++) {
                    // connect the two pastures in a new field
                    field newF;

                    // check the diameter of the new field
                    double diameter = findDiameter(newF);
                    // if new diameter is smaller than existing minimum, record it;
                    if (diameter < minDiameter) {
                        minDiameter = diameter;
                        minPastureA = fields[i].pastures[p1];
                        minPastureB = fields[j].pastures[p2];
                    }
                }
            }
        }
    }

    // writing output
    ofstream fout("cowtour.out");
    if (fout.is_open()) {
        fout << minDiameter << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}