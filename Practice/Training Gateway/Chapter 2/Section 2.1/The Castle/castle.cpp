/*
ID: daniel25
TASK: castle
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct component {
    int size;
    int nodes[22500][2];
};

int M, N;
int castle[150][150];
component components[22500];
int numComponents = 0;
int largestComponent = -1;
int largestCreatableRoom = -1;
int wallToRemove[1][1];

void intToWalls(int i, int row, int col) {
    if (i % 2 == 1) {
        castle[row][col-1] = 1;
        castle[row+1][col-1] = 1;
        castle[row-1][col-1] = 1;
        i -= 1;
    }
    if (i - 8 >= 0) {
        castle[row+1][col] = 1;
        castle[row+1][col+1] = 1;
        castle[row+1][col-1] = 1;
        i -= 8;
    }
    if (i - 4 >= 0) {
        castle[row][col+1] = 1;
        castle[row+1][col+1] = 1;
        castle[row-1][col+1] = 1;
        i -= 4;
    }
    if (i - 2 >= 0) {
        castle[row-1][col] = 1;
        castle[row-1][col+1] = 1;
        castle[row-1][col-1] = 1;
    }
}

void populateCastle(ifstream & fin) {
    int row = 0;
    for (int i = 1; i < 150; i += 2) {
        int col = 0;
        if (row == N)
            break;
        for (int j = 1; j < 150; j += 2) {
            if (col == M)
                break;
            int room;
            fin >> room;
            intToWalls(room, i, j);
            col += 1;
        }
        row += 1;
    }
}

void printCastle() {
    for (int i = 0; i < N*2+1; i++) {
        for (int j = 0; j < M*2+1; j++) {
            cout << castle[i][j] << " ";
        }
        cout << endl;
    }
}

void dfs(int x, int y, component & c, int i) {
    // assign current node to component
    c.nodes[i][0] = x;
    c.nodes[i][1] = y;
    c.size += 1;
    // mark current node visited
    castle[x][y] = 8;
    // recurse on neighbor nodes and mark them visited
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (castle[x+a][y+b] == 0)
                dfs(x+a, y+b, c, ++i);
        }
    }
}

void floodFill() {
    // for each node, if unvisited
    for (int i = 1; i < N*2; i++) {
        for (int j = 1; j < M*2; j++) {
            if (castle[i][j] == 0) {
                component c = component();
                dfs(i, j, c, 0);
                components[numComponents] = c;
                numComponents++;
            }
        }
    }
}

void findLargestComponent() {
    // call dfs on each unvisited node
    for (int i = 0; i < numComponents; i++) {
        components[i].size = components[i].size / 2 + 1;
        if (components[i].size > largestComponent)
            largestComponent = components[i].size;
    }
}

int main() {
    // reading input
    ifstream fin("castle.in");
    if (fin.is_open()) {
        fin >> M;
        fin >> N;
        populateCastle(fin);
    } else cout << "error opening input file" << endl;
    fin.close();

    printCastle();
    floodFill();
    cout << numComponents << endl;
    findLargestComponent();
    cout << largestComponent << endl;

    // writing output
    ofstream fout("castle.out");
    if (fout.is_open()) {
        fout << numComponents << "\n";
        fout << largestComponent << "\n";
        fout << largestCreatableRoom << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}