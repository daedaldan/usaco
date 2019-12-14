#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

struct farm {
    char cow;
    list<int> edges;
    bool visited = false;
    int index;
    int parent;
};

struct f {
    int a, b;
    char cowPrefer;
};

struct path {
    int a, b;
    bool operator<(const path & rhs) const {
        if (rhs.a == a)
            return b < rhs.b;
        else
            return a < rhs.a;
    }
};

struct cows {
    bool G;
    bool H;
    bool operator<(const cows & rhs) const {
        if (rhs.G == G)
            return H == rhs.H;
        else
            return G == rhs.G;
    }
};

int N, M;
string farmCows;
farm farms[100001];
f friends[100000];
map<path, cows> pathCows;
string solution;

void catalogPathCows(queue<farm> & q, int source) {
    q.push(farms[source]);
    farms[source].visited = true;
    while (!q.empty()) {
        farm f = q.front();
        q.pop();
        list<int>::const_iterator it;
        for (it = f.edges.begin(); it !=  f.edges.end(); ++it) {
            if (!farms[*it].visited) {
                q.push(farms[*it]);
                farms[*it].visited = true;
            }
        }
    }
}

int main() {
    // reading input
    ifstream fin("milkvisits.in");
    if (fin.is_open()) {
        fin >> N >> M;
        fin >> farmCows;
        // farms
        for (int i = 1; i <= N; i++) {
            farm f;
            f.cow = farmCows[i];
            f.index = i;
            farms[i] = f;
        }
        // edges
        for (int i = 0; i < N-1; i++) {
            int a, b;
            fin >> a >> b;
            farms[a].edges.push_back(b);
            farms[b].edges.push_back(a);
        }
        // friends
        for (int i = 0; i < M; i++) {
            f x;
            fin >> x.a >> x.b >> x.cowPrefer;
            friends[i] = x;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    queue<farm> q;
    catalogPathCows(q, 1);

    for (int i = 1; i < N+1; i++) {
        farms[i].visited = false;
    }

    for (int i = 0; i < M; i++) {
        queue<farm> q;
        while (!q.empty())
            q.pop();
        f x = friends[i];
        q.push(farms[x.a]);
        farms[x.a].visited = true;
        // bfs to find path from a to b
        while (!q.empty() && q.front().index != x.b) {
            farm f = q.front();
            q.pop();
            list<int>::const_iterator it;
            for (it = f.edges.begin(); it !=  f.edges.end(); ++it) {
                if (!farms[*it].visited) {
                    q.push(farms[*it]);
                    q.back();
                    farms[q.back().index].parent = f.index;
                    farms[*it].visited = true;
                }
            }
        }
        int numNodes = 0;
        farm f = farms[q.front().index];
        unordered_set<int> cows;
        // retrace path's cows
        while (f.index != x.a) {
            cows.insert(farms[f.index-1].cow);
            numNodes++;
            f = farms[f.parent];
        }

        // check if preferred cow is on path
        if (cows.find(x.cowPrefer) != cows.end()) {
            solution += "1";
        } else {
            solution += "0";
        }

        for (int i = 1; i < N+1; i++) {
            farms[i].visited = false;
        }
    }

    // writing output
    ofstream fout("milkvisits.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}