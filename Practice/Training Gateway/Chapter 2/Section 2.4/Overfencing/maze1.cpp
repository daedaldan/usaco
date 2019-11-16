/*
ID: daniel25
TASK: maze1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

struct node {
    int row;
    int col;
    int neighbors[4][2];
    int numNeighbors = 0;
    // for Dijkstra's
    int distance = 99999;
    bool visited = false;
};

int W;
int H;
node nodes[100];
int numNodes = 0;
//unordered_set<node> nodeHashTable;
char input[201][201];
node exits[2];
int numExits = 0;
int solution = -1;

void printInput() {
    for (int r = 0; r < H*2+1; r++) {
        for (int c = 0; c < W*2+1; c++) {
            cout << input[r][c];
        }
        cout << endl;
    }
}

void catalogNodesAndEdges() {
    for (int r = 1; r < H*2; r+=2) {
        for (int c = 1; c < W*2; c+=2) {
            // cataloging node
            node n;
            n.row = r;
            n.col = c;
            nodes[numNodes] = n;
//            nodeHashTable.insert(n);
            numNodes++;
            // cataloging edges
            if (input[r-1][c] == ' ' && r-1 == 0) {
                node exit;
                exit.row = r-1;
                exit.col = c;
                exits[numExits] = exit;
                numExits++;
            } else if (input[r-1][c] == ' ') {
                n.neighbors[n.numNeighbors][0] = r-2;
                n.neighbors[n.numNeighbors][1] = c;
                n.numNeighbors++;
            }
            if (input[r+1][c] == ' ' && r+1 == H*2) {
                node exit;
                exit.row = r+1;
                exit.col = c;
                exits[numExits] = exit;
                numExits++;
            } else if (input[r+1][c] == ' ') {
                n.neighbors[n.numNeighbors][0] = r+2;
                n.neighbors[n.numNeighbors][1] = c;
                n.numNeighbors++;
            }
            if (input[r][c-1] == ' ' && c-1 == 0) {
                node exit;
                exit.row = r;
                exit.col = c-1;
                exits[numExits] = exit;
                numExits++;
            } else if (input[r][c-1] == ' ') {
                n.neighbors[n.numNeighbors][0] = r;
                n.neighbors[n.numNeighbors][1] = c-2;
                n.numNeighbors++;
            }
            if (input[r][c+1] == ' ' && c+1 == W*2) {
                node exit;
                exit.row = r;
                exit.col = c+1;
                exits[numExits] = exit;
                numExits++;
            } else if (input[r][c+1] == ' ') {
                n.neighbors[n.numNeighbors][0] = r;
                n.neighbors[n.numNeighbors][1] = c+2;
                n.numNeighbors++;
            }
        }
    }
}

node findMinUnvisitedNode() {
    node min;
    min.distance = 999999;
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < min.distance && !nodes[i].visited) {
            min = nodes[i];
        }
    }

    return min;
}

int dijkstrasMax() {
    exits[0].distance = 0;
    int nodesVisited = 0;

    while (nodesVisited < numNodes) {
        node cur = findMinUnvisitedNode();

        cur.visited = true;
        nodesVisited++;

        for (int i = 0; i < cur.numNeighbors; i++) {
            if (cur.distance + 1 < cur.neighbors[i].distance) {
                cur.neighbors[i].distance = cur.distance + 1;
            }
        }
    }

    exits[1].distance = 0;
    nodesVisited = 0;

    while (nodesVisited < numNodes) {
        node cur = findMinUnvisitedNode();

        cur.visited = true;
        nodesVisited++;

        for (int i = 0; i < cur.numNeighbors; i++) {
            if (cur.distance + 1 < cur.neighbors[i].distance) {
                cur.neighbors[i].distance = cur.distance + 1;
            }
        }
    }

    int maxDistance = -1;
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance > maxDistance)
            maxDistance = nodes[i].distance;
    }

    return maxDistance;
}

int main() {
    // reading input
    ifstream fin("maze1.in");
    if (fin.is_open()) {
        fin >> W;
        fin >> H;
        fin >> noskipws;
        char unit;
        int r = 0;
        while (r < H*2+1) {
            int c = 0;
            while (c < W*2+1) {
                fin >> unit;
                if (unit != '\n' && unit != '\r') {
                    input[r][c] = unit;
                    c++;
                }
            }
            r++;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    catalogNodesAndEdges();

    printInput();

    solution = dijkstrasMax();

    // writing output
    ofstream fout("maze1.out");
    if (fout.is_open()) {
        fout << solution;
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}