/*
ID: daniel25
TASK: cowtour
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

struct pasture {
    int x;
    int y;
    int index;
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
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
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

double findDiameter(int fieldPastures[], int numPastures) {
    sort(fieldPastures, fieldPastures+numPastures);
    double dist[150][150];
    if (edges[2][6]) {
        for (int i = 0; i < numPastures; i++) {
            cout << fieldPastures[i] << ": " << pastures[fieldPastures[i]].x << ", " << pastures[fieldPastures[i]].y << endl;
        }
    }

    // start with all single edge paths
    for (int i = 0; i < numPastures; i++) {
        for (int j = 0; j < numPastures; j++) {
            if (edges[fieldPastures[i]][fieldPastures[j]] == 1) {
                if ((fieldPastures[i] == 2 && fieldPastures[j] == 6) || (fieldPastures[i] == 6 && fieldPastures[j] == 2)) {
                    cout << "distance between C and G: " << distance(pastures[fieldPastures[i]], pastures[fieldPastures[j]]) << endl;
                }
                dist[fieldPastures[i]][fieldPastures[j]] = distance(pastures[fieldPastures[i]], pastures[fieldPastures[j]]);
            } else {
                dist[fieldPastures[i]][fieldPastures[j]] = 1000000000;
            }
        }
    }

    // find all-pairs shortest paths
    for (int k = 0; k < numPastures; k++) {
        for (int i = 0; i < numPastures; i++) {
            for (int j = 0; j < numPastures; j++) {
                if (edges[fieldPastures[i]][fieldPastures[k]] == 1
                 && edges[fieldPastures[j]][fieldPastures[k]] == 1) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        if (edges[2][6]) {
                            cout << i << " " << j << " " << dist[i][j] << endl;
                        }
                    }
                }
            }
        }
    }

    double distance = -1;
    // find maximum shortest path
    for (int i = 0; i < numPastures; i++) {
        for (int j = 0; j < numPastures; j++) {
            if (edges[2][6])
                cout << dist[i][j] << endl;
            if (dist[i][j] > distance && dist[i][j] != 1000000000 && i != j) {
                distance = dist[i][j];
            }
        }
    }

    return distance;
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
            p.index = i;
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
                    // connect the two pastures
                    edges[fields[i].pastures[p1].index][fields[j].pastures[p2].index] = 1;
                    // make list of which pastures are in the new field for Floyd-Warshall
                    int pasturesInField[150];
                    int numPasturesInField = 0;
                    for (int a = 0; a < fields[i].numPastures; a++) {
                        pasturesInField[numPasturesInField] = fields[i].pastures[a].index;
                        numPasturesInField++;
                    }
                    for (int a = 0; a < fields[j].numPastures; a++) {
                        pasturesInField[numPasturesInField] = fields[j].pastures[a].index;
                        numPasturesInField++;
                    }
                    // check the diameter of the new field
                    double diameter = findDiameter(pasturesInField, numPasturesInField);
                    // if new diameter is smaller than existing minimum, record it;
                    if (diameter < minDiameter) {
                        minDiameter = diameter;
                        minPastureA = fields[i].pastures[p1];
                        minPastureB = fields[j].pastures[p2];
                    }
                    // unconnect the two pastures
                    edges[fields[i].pastures[p1].index][fields[j].pastures[p2].index] = 0;
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