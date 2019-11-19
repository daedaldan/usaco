/*
ID: daniel25
TASK: comehome
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>

using namespace std;

struct node {
    char name;
    int distance = 520001;
    bool visited = false;
};

int P;
int edges[58][58];
bool pastures[58];
bool cows[58];
node nodes[58];
int numNodes = 0;
map<int, int> nameToNodeI;
int barnIndex = -1;
int minDistance = 999999999;
char minCow = '0';

int findMinDistanceNode() {
    int minNode = -1;
    int minDistance = 520002;
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < minDistance && !nodes[i].visited) {
            minNode = i;
            minDistance = nodes[i].distance;
        }
    }

    return minNode;
}

void dijkstras() {
    nodes[barnIndex].distance = 0;
    int numVisited = 0;
    while (numVisited < numNodes) {
        int cur = findMinDistanceNode();

        nodes[cur].visited = true;
        numVisited++;

        for (int i = 0; i < 58; i++) {
            int curNum = nodes[cur].name - 65;
            if (edges[curNum][i] != 0) {
                if (nodes[cur].distance + edges[curNum][i] < nodes[nameToNodeI[i]].distance) {
                    nodes[nameToNodeI[i]].distance = nodes[cur].distance + edges[curNum][i];
                }
            }
        }
    }
}

int main() {
    // reading input
    ifstream fin("comehome.in");
    if (fin.is_open()) {
        fin >> P;
        for (int i = 0; i < P; i++) {
            char start;
            char end;
            int weight;
            fin >> start;
            fin >> end;
            fin >> weight;
            if (weight < edges[start-65][end-65] || edges[start-65][end-65] == 0)
                edges[start-65][end-65] = weight;
            if (weight < edges[end-65][start-65] || edges[end-65][start-65] == 0)
                edges[end-65][start-65] = weight;
            // remembering pastures
            pastures[start-65] = true;
            pastures[end-65] = true;
            // remembering which pastures have cows
            if (start < 91) {
                cows[start-65] = true;
            }
            if (end < 91) {
                cows[end-65] = true;
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // converting pastures to nodes
    for (int i = 0; i < 58; i++) {
        if (pastures[i]) {
            node n;
            n.name = static_cast<char>(i+65);
            nodes[numNodes] = n;
            if (i == 25)
                barnIndex = numNodes;
            nameToNodeI[i] = numNodes;
            numNodes++;
        }
    }

    dijkstras();

    // find minimum distance and associated cow
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < minDistance && i != barnIndex && cows[nodes[i].name-65]) {
            minDistance = nodes[i].distance;
            minCow = nodes[i].name;
        }
    }

    // writing output
    ofstream fout("comehome.out");
    if (fout.is_open()) {
        fout << minCow << " " << minDistance << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}