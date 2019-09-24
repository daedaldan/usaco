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
    int nodes[500][2];
};

int M, N;
int castle[150][150];
component components[500];
int numComponents = 0;
int largestComponent = -1;
int largestCreatableRoom = -1;
int wallToRemove[2];
string wtrDirection;

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
    cout << endl;
}

void dfs(int y, int x, component & c, int i) {
    // assign current node to component
    c.nodes[i][0] = y;
    c.nodes[i][1] = x;
    c.size += 1;
    // mark current node visited
    castle[y][x] = 8;
    // recurse on neighbor nodes and mark them visited
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (castle[y+a][x+b] == 0)
                dfs(y+a, x+b, c, ++i);
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

bool moreOptimal(int y, int x, int optimal[2]) {
    if (x < optimal[1])
        return true;
    if (y < optimal[0])
        return true;

    return false;
}

void findSize(int y, int x, int & size, int copyCastle[150][150]) {
    // add current node and mark visited
    size += 1;
    copyCastle[y][x] = 0;
    // recurse on neighbor nodes and mark them visited
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            if (copyCastle[y+a][x+b] == 8 && (a == 0 || b == 0)) {
                findSize(y+a, x+b, size, copyCastle);
            }
        }
    }
}

void findBreakWall() {
    for (int i = N*2-1; i > 0; i--) {
        for (int j = 1; j < M*2; j++) {
            if (castle[i][j] == 1) {
                int copyCastle[150][150];
                for (int i = 0; i < N*2+1; i++)
                    for (int j = 0; j < M*2+1; j++)
                        copyCastle[i][j] = castle[i][j];
                int size = 0;
                findSize(i, j, size, copyCastle);
                size = size / 2 + 1;
                if (size > largestCreatableRoom) {
                    largestCreatableRoom = size;
                    wallToRemove[0] = i;
                    wallToRemove[1] = j;
                }
            }
        }
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

//    printCastle();
    floodFill();
    findLargestComponent();
    findBreakWall();

    if (castle[wallToRemove[0]+1][wallToRemove[1]] == 8)
        wtrDirection = "N";
    else
        wtrDirection = "E";
    wallToRemove[0] = wallToRemove[0] / 2 + 1;
    if (wallToRemove[1] != 1)
        wallToRemove[1] = wallToRemove[1] / 2;

    // writing output
    ofstream fout("castle.out");
    if (fout.is_open()) {
        fout << numComponents << "\n";
        fout << largestComponent << "\n";
        fout << largestCreatableRoom << "\n";
        fout << wallToRemove[0] << " " << wallToRemove[1] << " " << wtrDirection << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}