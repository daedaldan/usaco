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
    int distance = 1001;
    bool visited = false;
};

int P;
int edges[26][26];
bool pastures[26];
bool cows[26];
node nodes[26];
int numNodes = 0;
map<int, int> nameToNodeI;
int barnIndex = -1;
int minDistance = 999999999;
char minCow = '0';

int findMinDistanceNode() {
    int minNode = -1;
    int minDistance = 1002;
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < minDistance && !nodes[i].visited) {
            minNode = i;
        }
    }

    return minNode;
}

void dijkstras() {
    nodes[barnIndex].distance = 0;
    int numVisited = 0;
    while (numVisited < numNodes) {
        int cur = findMinDistanceNode();
//        cout << nodes[cur].name << " " << nodes[cur].distance << endl;

        nodes[cur].visited = true;
        numVisited++;

        for (int i = 0; i < 26; i++) {
            int curNum = tolower(nodes[cur].name) - 97;
            if (edges[curNum][i] != 0) {
                cout << edges[curNum][i] << endl;
                cout << nodes[nameToNodeI[i]].name << " " << nodes[nameToNodeI[i]].distance << endl;
                cout << "   " << nodes[cur].name << " " << nodes[cur].distance << endl;
                // fix this
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
            edges[tolower(start)-97][tolower(end)-97] = weight;
            edges[tolower(end)-97][tolower(start)-97] = weight;
            // remembering pastures
            pastures[tolower(start)-97] = true;
            pastures[tolower(end)-97] = true;
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
    for (int i = 0; i < 26; i++) {
        if (pastures[i]) {
            node n;
            if (cows[i])
                n.name = static_cast<char>(i+65);
            else
                n.name = static_cast<char>(i+97);
            nodes[numNodes] = n;
            if (i == 25)
                barnIndex = numNodes;
            nameToNodeI[i] = numNodes;
            numNodes++;
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    dijkstras();

    // find minimum distance and associated cow
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].distance < minDistance && i != barnIndex && cows[i]) {
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