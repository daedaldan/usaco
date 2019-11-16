/*
ID: daniel25
TASK: maze1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

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
char input[201][201];
node exits[2];
int numExits = 0;
int exitNodes[2];
int numExitNodes = 0;
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
            input[r][c] = static_cast<char>(numNodes);
            // cataloging edges
            if (input[r-1][c] == ' ' && r-1 == 0) {
                node exit;
                exit.row = r-1;
                exit.col = c;
                exits[numExits] = exit;
                numExits++;
                exitNodes[numExitNodes] = numNodes;
                numExitNodes++;
            } else if (input[r-1][c] == ' ') {
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][0] = r-2;
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][1] = c;
                nodes[numNodes].numNeighbors++;
            }
            if (input[r+1][c] == ' ' && r+1 == H*2) {
                node exit;
                exit.row = r+1;
                exit.col = c;
                exits[numExits] = exit;
                numExits++;
                exitNodes[numExitNodes] = numNodes;
                numExitNodes++;
            } else if (input[r+1][c] == ' ') {
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][0] = r+2;
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][1] = c;
                nodes[numNodes].numNeighbors++;
            }
            if (input[r][c-1] == ' ' && c-1 == 0) {
                node exit;
                exit.row = r;
                exit.col = c-1;
                exits[numExits] = exit;
                numExits++;
                exitNodes[numExitNodes] = numNodes;
                numExitNodes++;
            } else if (input[r][c-1] == ' ') {
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][0] = r;
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][1] = c-2;
                nodes[numNodes].numNeighbors++;
            }
            if (input[r][c+1] == ' ' && c+1 == W*2) {
                node exit;
                exit.row = r;
                exit.col = c+1;
                exits[numExits] = exit;
                numExits++;
                exitNodes[numExitNodes] = numNodes;
                numExitNodes++;
            } else if (input[r][c+1] == ' ') {
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][0] = r;
                nodes[numNodes].neighbors[nodes[numNodes].numNeighbors][1] = c+2;
                nodes[numNodes].numNeighbors++;
                nodes[numNodes].distance = 1;
            }
            numNodes++;
        }
    }
}

int findMinUnvisitedNode() {
    int minNodeI = 1;
    int minDistance = 9999999;
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < minDistance && !nodes[i].visited) {
            minNodeI = i;
            minDistance = nodes[i].distance;
        }
    }

    return minNodeI;
}

int dijkstrasMax() {
    // dijkstra's from first exit
    nodes[exitNodes[0]].distance = 1;
    int nodesVisited = 0;

    while (nodesVisited < numNodes) {
        int cur = findMinUnvisitedNode();

        nodes[cur].visited = true;
        nodesVisited++;

        for (int i = 0; i < nodes[cur].numNeighbors; i++) {
            node neighbor = nodes[input[nodes[cur].neighbors[i][0]][nodes[cur].neighbors[i][1]]];
            if (nodes[cur].distance + 1 < neighbor.distance) {
                nodes[input[nodes[cur].neighbors[i][0]][nodes[cur].neighbors[i][1]]].distance = nodes[cur].distance + 1;
            }
        }
    }

    // resetting stats
    for (int i = 0; i < numNodes; i++) {
        nodes[i].distance = 99999;
        nodes[i].visited = false;
    }

    // dijkstra's from second exit
    nodes[exitNodes[1]].distance = 1;
    nodesVisited = 0;

    while (nodesVisited < numNodes) {
        int cur = findMinUnvisitedNode();

        nodes[cur].visited = true;
        nodesVisited++;

        for (int i = 0; i < nodes[cur].numNeighbors; i++) {
            node neighbor = nodes[input[nodes[cur].neighbors[i][0]][nodes[cur].neighbors[i][1]]];
            if (nodes[cur].distance + 1 < neighbor.distance) {
                nodes[input[nodes[cur].neighbors[i][0]][nodes[cur].neighbors[i][1]]].distance = nodes[cur].distance + 1;
            }
        }
    }


    // finding max distance shortest path
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

    printInput();

    catalogNodesAndEdges();

    solution = dijkstrasMax();

    // writing output
    ofstream fout("maze1.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}